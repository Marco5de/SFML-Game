//
// Created by marco on 23.12.19.
//

#include <iostream>
#include "Network.h"

#define LOGGING_LEVEL_1

#include "logger.h"

//todo really bad code! --> clean up!
//define for global usage!
NetworkData::NetworkDataBuffer NetworkData::networkDataBuffer = {};

/**
 * @brief non static function, called by ws dispatch!
 * @notes puts incoming message in shared struct, then parser is called
 * @param message
 */
void networkCallback(const std::string &message) {
    NetworkData::networkDataBuffer.updated = true;
    NetworkData::networkDataBuffer.globalStringData = message;
}

int Network::initNetwork() {
    ws = WebSocket::from_url("ws://localhost:4444");
    assert(ws);

    messageParser = IncomingMessageParser();

    return 1;
}

//todo in der gesendet nachricht steht als typ auch nur 1 drin --> muss überall ein string rein!
void Network::handleNetwork() {
    if (ws->getReadyState() != WebSocket::CLOSED) {
        ws->poll(); //does not block by default!
        ws->dispatch(networkCallback);
    }

    if (NetworkData::networkDataBuffer.updated) {
        NetworkData::networkDataBuffer.updated = false;
        messageParser.parseMessage(NetworkData::networkDataBuffer.globalStringData);
    }
    //having to use explicit block ({}) around cases!
    switch (NetworkData::networkDataBuffer.state) {
        case networkState::welcome:
            LOG("Received welcome Message");
            //fetch update!
            NetworkData::networkDataBuffer.state = networkState::getAvailableLobbies;
            break;
        case networkState::createLobby: {
            LOG("Create new Lobby");
            class CreateNewLobby cnl(NetworkData::networkDataBuffer.UUID, NetworkData::networkDataBuffer.lobbyname);
            ws->send(cnl.getMessageString());
            //fetch update!
            NetworkData::networkDataBuffer.state = networkState::getAvailableLobbies;
            break;
        }
        case networkState::getAvailableLobbies: {
            LOG("Get Available Lobbies");
            class GetAvailableLobbies gal(NetworkData::networkDataBuffer.UUID);
            ws->send(gal.getMessageString());
            NetworkData::networkDataBuffer.state = networkState::idle;
            break;
        }
        case networkState::joinLobby: {
            //todo remove hardcoded username!
            if(NetworkData::networkDataBuffer.insideLobby)
                break;
            LOG("Joined Lobby");
            //evtl out of bounds!
            std::string LID = NetworkData::networkDataBuffer.lobbyVec[NetworkData::networkDataBuffer.lobbyIndex].lobbyID;
            class JoinLobby jl(NetworkData::networkDataBuffer.UUID, LID, "Marco");
            ws->send(jl.getMessageString());
            NetworkData::networkDataBuffer.state = networkState::getAvailableLobbies;
            NetworkData::networkDataBuffer.insideLobby = true;
            break;
        }
        case networkState::leaveLobby: {
            if(!NetworkData::networkDataBuffer.insideLobby)
                break;
            LOG("Leave Lobby");
            //todo select which lobby is left!
            std::string LID = NetworkData::networkDataBuffer.lobbyVec[NetworkData::networkDataBuffer.lobbyIndex].lobbyID;
            class LeaveLobby ll(NetworkData::networkDataBuffer.UUID, LID);
            ws->send(ll.getMessageString());
            NetworkData::networkDataBuffer.state = networkState::getAvailableLobbies;
            NetworkData::networkDataBuffer.insideLobby = false;
            break;
        }
        case networkState::startGame: {
            LOG("Start Game");
            std::string LID = NetworkData::networkDataBuffer.lobbyVec[NetworkData::networkDataBuffer.lobbyIndex].lobbyID;
            class StartGame sg(NetworkData::networkDataBuffer.UUID,LID);
            ws->send(sg.getMessageString());
            NetworkData::networkDataBuffer.state = networkState::idle;
        }

    }

}


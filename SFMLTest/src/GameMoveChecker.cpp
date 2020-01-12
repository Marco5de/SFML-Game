//
// Created by marco on 20.12.19.
//

#include "GameMoveChecker.h"


/**
 * @brief           returns id's of indirect neighbors of a given tile inside a std::vector
 * @param tile      selected tile, to get neighbors of
 * @return          std::vector<int> containing the indirect neighbors
 */
auto GameMoveChecker::getIndirectNeighbors(Tile &tile) -> std::vector<int> {
    std::vector<int> directNeighbors = neighbors[tile.getID()];
    std::vector<int> nOfn(0);
    //contains all neighbors and neighbors of neighbors
    for(int id : directNeighbors){
        std::vector<int> indirectNeighbors = neighbors[id];
        nOfn.insert(nOfn.end(),indirectNeighbors.begin(),indirectNeighbors.end());
    }
    //remove direct neighbors
    for(int val : directNeighbors){
        std::vector<int>::iterator it;
        while((it=std::find(nOfn.begin(),nOfn.end(),val)) != nOfn.end())
            nOfn.erase(it);
    }
    //remove myself from nOfn
    std::vector<int>::iterator it;
    while((it=std::find(nOfn.begin(),nOfn.end(),tile.getID())) != nOfn.end())
        nOfn.erase(it);

    return nOfn;
}

auto GameMoveChecker::getIndirectNeighbors(int tileID) -> std::vector<int> {
    std::vector<int> directNeighbors = neighbors[tileID];
    std::vector<int> nOfn(0);
    //contains all neighbors and neighbors of neighbors
    for(int id : directNeighbors){
        std::vector<int> indirectNeighbors = neighbors[id];
        nOfn.insert(nOfn.end(),indirectNeighbors.begin(),indirectNeighbors.end());
    }
    //remove direct neighbors
    for(int val : directNeighbors){
        std::vector<int>::iterator it;
        while((it=std::find(nOfn.begin(),nOfn.end(),val)) != nOfn.end())
            nOfn.erase(it);
    }
    //remove myself from nOfn
    std::vector<int>::iterator it;
    while((it=std::find(nOfn.begin(),nOfn.end(),tileID)) != nOfn.end())
        nOfn.erase(it);

    return nOfn;
}

int GameMoveChecker::checkMove(int selectedField, int target) {
    auto it = std::find(forbiddenFields.begin(),forbiddenFields.end(),target);
    bool invalidTarget = it != forbiddenFields.end();
    if(selectedField == target || invalidTarget)
        return INVALID_MOVE;

    std::vector<int> directNeighbors = neighbors[selectedField];
    if(std::find(directNeighbors.begin(),directNeighbors.end(),target) != directNeighbors.end())
        return DUPLICATE;

    std::vector<int> indirectNeighbors = this->getIndirectNeighbors(selectedField);
    if(std::find(indirectNeighbors.begin(),indirectNeighbors.end(),target) != indirectNeighbors.end())
        return SIMPLE_MOVE;

    return INVALID_MOVE;
}


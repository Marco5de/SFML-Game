//
// Created by marco on 20.12.19.
//

#ifndef SFMLTEST_CENTERING_H
#define SFMLTEST_CENTERING_H

#include <SFML/Graphics.hpp>
namespace Centering {

    void center(sf::RectangleShape &outer, sf::Text &inner) {
        float x = outer.getGlobalBounds().left + .5 * outer.getGlobalBounds().width - 0.5 * inner.getGlobalBounds().width;
        float y = outer.getGlobalBounds().top + .5 * outer.getGlobalBounds().height - 0.5 * inner.getGlobalBounds().height;
        inner.setPosition(x, y);
    }

}
#endif //SFMLTEST_CENTERING_H

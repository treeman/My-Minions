#pragma once

#include <vector>
#include <boost/foreach.hpp>

#include "Tree/InputHandler.hpp"
#include "Order.hpp"

class Controller : public Tree::InputHandler {
public:
    virtual ~Controller() { }

    void AddOrderHandler( OrderHandler *handler )
    {
        order_handlers.push_back( handler );
    }

    virtual bool HandleEvent( sf::Event & ) { return true; }
    virtual void Update( float ) { }
protected:
    typedef std::vector<OrderHandler*> OrderHandlers;
    OrderHandlers order_handlers;

    void SendOrder( Order order )
    {
        BOOST_FOREACH( OrderHandler *handler, order_handlers ) {
            handler->HandleOrder( order );
        }
    }
};


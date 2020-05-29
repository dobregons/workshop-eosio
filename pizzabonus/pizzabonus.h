#pragma once

#include <eosio/eosio.hpp>
#include "./tables.h"

using eosio::name;
using eosio::contract;

class [[eosio::contract]] pizzabonus : public contract {
  public:
    using contract::contract;
    
    pizzabonus(name self_contract, name user, eosio::datastream<const char*> ds);
    // ~pizzabonus();

    [[eosio::action]]
    void init();

    [[eosio::action]]
    void buypizza(name user);

    [[eosio::action]]
    uint16_t getcoupons(name user);

    [[eosio::action]]
    void redeemcoupon(name user);

    [[eosio::action]]
    void chngthrhld(name user, uint16_t newvalue);

  private:
    usertable_t ut;

    config_t config;
};
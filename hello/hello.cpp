#include <eosio/eosio.hpp>

class [[eosio::contract]] hello : public eosio::contract
{
    public:
        using contract::contract;

        [[eosio::action]]
        void hi(eosio::name user)
        {
            eosio::print("Hello", user);
        }
};
#include <eosio/tester.hpp>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

class pizzabonus_tester {
public: 
  eosio::test_chain chain;

  pizzabonus_tester() {
    auto file_binary = eosio::read_whole_file("./pizzabonus_test.wasm");
    eosio::name contract_account("pizzabonus");
    eosio::permission_level permission{"eosio"_n, "active"_n};
    std::tuple file = std::make_tuple(contract_account, uint8_t{0}, uint8_t{0}, file_binary);

    chain.create_code_account(contract_account, true);
    chain.transact(
      {
        eosio::action{ permission, "eosio"_n, "susetcode"_n, file}
      },
      "Error has happened"
    );

  }
};

TEST_CASE("case1", "") {
  pizzabonus_tester tester;

  tester.chain.create_account("david"_n);
  tester.chain.create_account("shymmy"_n);
  tester.chain.start_block();

  tester.chain.finish_block();

  REQUIRE(1 + 1 == 2);
}

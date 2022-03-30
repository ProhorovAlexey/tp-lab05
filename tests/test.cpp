#include <gtest/gtest.h>

#include <Transaction.h>
#include <Account.h>

TEST(Transaction, fee){
  Account roflan(1, 102);
  Account potsan(2, 0);
  Account weak(3, 100);

  Transaction transaction;
  EXPECT_TRUE(transaction.Make(roflan, potsan, 100));
  EXPECT_FALSE(transaction.Make(weak, potsan, 100));
  weak.Lock();
  weak.ChangeBalance(-10);
  weak.Unlock();
  EXPECT_FALSE(transaction.Make(weak, potsan, 100));
  EXPECT_EQ(transaction.fee(), 1);
  transaction.set_fee(51);
  EXPECT_FALSE(transaction.Make(roflan, potsan, 100));
}

TEST(Transaction, Exeptions){
    Account roflan(1, 102);
    Account potsan(1, 0);
    Account sec_potsan(2, 0);

    Transaction transaction;

    try {
        transaction.Make(roflan, potsan, 100);
        FAIL() << "expected std::logic_error";
    } catch (std::logic_error& error){
        std::cout << error.what() << '\n';
        EXPECT_EQ(error.what(), std::string("invalid action"));
    } catch (...){
        FAIL() << "expected std::logic_error";
    }

    try {
        transaction.Make(roflan, sec_potsan, -100);
        FAIL() << "expected std::invalid_argument";
    } catch (std::invalid_argument& error){
        std::cout << error.what() << '\n';
        EXPECT_EQ(error.what(), std::string("sum can't be negative"));
    } catch (...){
        FAIL() << "expected std::invalid_argument";
    }

    try {
        transaction.Make(roflan, sec_potsan, 90);
        FAIL() << "expected std::logic_error";
    } catch (std::logic_error& error){
        std::cout << error.what() << '\n';
        EXPECT_EQ(error.what(), std::string("too small"));
    } catch (...){
        FAIL() << "expected std::logic_error";
    }
}

TEST(Account, Balance){
    Account roflan(1, 123);
    Account potsan(2, 9999);

    EXPECT_EQ(roflan.GetBalance(), 123);
    EXPECT_EQ(potsan.GetBalance(), 9999);

    roflan.Lock();
    roflan.ChangeBalance(10);
    EXPECT_EQ(roflan.GetBalance(), 133);
}

TEST(Account, Id){
    Account roflan(1, 123);
    Account potsan(2, 9999);

    EXPECT_EQ(roflan.id(), 1);
    EXPECT_EQ(potsan.id(), 2);
}

TEST(Account, Lock){
    Account roflan(1, 123);
    Account potsan(2, 9999);

    EXPECT_ANY_THROW(roflan.ChangeBalance(10));
    roflan.Lock();
    EXPECT_ANY_THROW(roflan.Lock());
}
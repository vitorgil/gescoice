#include <gtest/gtest.h>

#include "Containers.h"
#include "Ingredients.h"
#include "IO.h"
#include "Lot.h"

#include <exception>

#include <QJsonDocument>

class TestContainers
{
public:
    TestContainers()
    {
        Containers::add("c1", 0.75, 0.9);
        Containers::add("c2", 10, 5.25);
    }
    ~TestContainers()
    {
        Containers::remove("c1");
        Containers::remove("c2");
    }
};

class TestIngredients
{
public:
    TestIngredients()
    {
        Ingredients::add("i1", 1.2);
        Ingredients::add("i2", 3.1);
    }
    ~TestIngredients()
    {
        Ingredients::remove("i1");
        Ingredients::remove("i2");
    }
};

TEST(CoreTest, Container)
{
    Container c("c1", 0.75, 1.2);
    ASSERT_TRUE(c.m_name == "c1");
    ASSERT_TRUE(c.m_capacityLiters == 0.75);
    ASSERT_TRUE(c.m_price == 1.2);
}

TEST(CoreTest, Containers)
{
    // Empty; no containers known
    ASSERT_TRUE(Containers::getAll().isEmpty());
    ASSERT_TRUE(Containers::get("c1").get() == nullptr);
    ASSERT_NO_THROW(Containers::remove("c1"));

    // Add container
    ASSERT_NO_THROW(Containers::add("c1", 20, 10.5));
    ASSERT_TRUE(Containers::getAll().size() == 1);
    // Re-add
    ASSERT_NO_THROW(Containers::add("c1", 20, 10.7));
    ASSERT_TRUE(Containers::getAll().size() == 1);

    // Add another one
    ASSERT_NO_THROW(Containers::add("c2", 20, 11.7));
    ASSERT_TRUE(Containers::getAll().size() == 2);

    // Should know c1
    ASSERT_TRUE(Containers::get("c1").get()->m_price == 10.7);
    ASSERT_TRUE(Containers::get("c2").get()->m_price == 11.7);

    // Clear added containers
    ASSERT_NO_THROW(Containers::remove("c1"));
    ASSERT_NO_THROW(Containers::remove("c2"));
    ASSERT_TRUE(Containers::getAll().isEmpty());
}

TEST(CoreTest, Ingredients)
{
    // Empty; no ingredients known
    ASSERT_TRUE(Ingredients::getAll().isEmpty());
    ASSERT_TRUE(Ingredients::getPrice("i1") < 0);
    ASSERT_NO_THROW(Ingredients::remove("i1"));

    // Add ingredient
    ASSERT_NO_THROW(Ingredients::add("i1", 1));
    ASSERT_TRUE(Ingredients::getAll().size() == 1);
    // Re-add
    ASSERT_NO_THROW(Ingredients::add("i1", 2));
    ASSERT_TRUE(Ingredients::getAll().size() == 1);
    
    // Add another one
    ASSERT_NO_THROW(Ingredients::add("i2", 2.5));
    ASSERT_TRUE(Ingredients::getAll().size() == 2);

    ASSERT_TRUE(Ingredients::getPrice("i1") == 2);
    ASSERT_TRUE(Ingredients::getPrice("i2") == 2.5);

    // Clear added ingredients
    ASSERT_NO_THROW(Ingredients::remove("i1"));
    ASSERT_NO_THROW(Ingredients::remove("i2"));
    ASSERT_TRUE(Ingredients::getAll().isEmpty());
}

TEST(CoreTest, IO)
{
    QJsonDocument doc;
    ASSERT_NO_THROW(IO::saveJson("", doc));
    ASSERT_NO_THROW(IO::readJson(""));
}

TEST(CoreTest, Lot_empty)
{
    Lot lot;
    ASSERT_NO_THROW(lot.removeContainer("c1"));
    ASSERT_NO_THROW(lot.removeIngredient("i1"));

    ASSERT_TRUE(lot.getContainers().isEmpty());
    ASSERT_TRUE(lot.getIngredients().isEmpty());
    ASSERT_TRUE(lot.getLastPrices().isEmpty());

    ASSERT_TRUE(lot.totalCost() == 0.0);
    ASSERT_NO_THROW(lot.calculatePrices());
    
    ASSERT_TRUE(lot.getContainers().isEmpty());
    ASSERT_TRUE(lot.getIngredients().isEmpty());
    ASSERT_TRUE(lot.getLastPrices().isEmpty());
    ASSERT_TRUE(lot.totalCost() == 0.0);
}

TEST(CoreTest, Lot)
{
    TestContainers tc;
    TestIngredients ti;

    Lot lot;
    ASSERT_NO_THROW(lot.addContainer("c1", 8));
    ASSERT_TRUE(lot.getContainers().size() == 1);
    ASSERT_NO_THROW(lot.addContainer("c1", 10));
    ASSERT_TRUE(lot.getContainers().size() == 1);

    ASSERT_NO_THROW(lot.calculatePrices());
    ASSERT_TRUE(lot.getLastPrices().isEmpty());
    ASSERT_TRUE(lot.totalCost() == 0.0);

    ASSERT_NO_THROW(lot.addIngredient("i1", 1000));
    ASSERT_TRUE(lot.getIngredients().size() == 1);
    ASSERT_NO_THROW(lot.addIngredient("i1", 1500));
    ASSERT_TRUE(lot.getIngredients().size() == 1);

    ASSERT_NO_THROW(lot.calculatePrices());
    ASSERT_FALSE(lot.getLastPrices().isEmpty());
    ASSERT_TRUE(lot.totalCost() > 0.0);
}

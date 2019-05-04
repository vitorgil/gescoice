#include <gtest/gtest.h>

#include "Ingredients.h"

#include <exception>

// Recipe getRecipe()
// {
//     Recipe r("Belga", 1);
//     r.addIngredient("açucar", 100);
//     r.addIngredient("malte", 300);
//     return r;
// }

// TEST(CoreTest, Recipe)
// {
//     Recipe r("Belga", 1);
//     ASSERT_TRUE("Belga" == r.m_name);
//     r.addIngredient("açucar", 1000);
//     ASSERT_TRUE(r.m_ingredientQuantities.size() == 1);
//     ASSERT_TRUE(r.m_ingredientQuantities["açucar"] == 1000);
// }

// TEST(CoreTest, Recipes)
// {
//     // empty
//     ASSERT_ANY_THROW(Recipes::getRecipe("Belga"));

//     // add one
//     auto r = getRecipe();
//     ASSERT_TRUE(Recipes::add(r));
    
//     ASSERT_NO_THROW(Recipes::getRecipe("Belga"));
//     // TODO add operator==
//     ASSERT_TRUE(r.m_name == Recipes::getRecipe("Belga").m_name);

//     // unknown recipe
//     ASSERT_ANY_THROW(Recipes::getRecipe("SomeRecipe"));
// }

TEST(CoreTest, Ingredients)
{
    // empty
    //ASSERT_ANY_THROW(Ingredients::getPrice("sugar"));

    // add and check
    ASSERT_NO_THROW(Ingredients::add("sugar", 1));
    ASSERT_TRUE(Ingredients::getPrice("sugar") == 1);

    // add the same, different price
    ASSERT_NO_THROW(Ingredients::add("sugar", 1.5));
    ASSERT_TRUE(Ingredients::getPrice("sugar") == 1.5);

    // add another one, old price doesn't change
    ASSERT_NO_THROW(Ingredients::add("sugar_2", 2));
    ASSERT_TRUE(Ingredients::getPrice("sugar") == 1.5);
}

//TEST(CoreTest, Brew)
//{
//    auto r = getRecipe();
//    Brew b(r, 500);
//
//    // prices are not known to ingredients
//    //ASSERT_ANY_THROW(b.calculateBottlePrice());
//
//    // add some prices
//    Ingredients::add("açucar", 1);
//
//    // still incomplete price information
//    //ASSERT_ANY_THROW(b.calculateBottlePrice());
//
//    Ingredients::add("malte", 10);
//
//    auto price = b.calculateBottlePrice();
//
//    // price estimation
//    double ratio = 500 / 1;
//    double estimatedPrice = (ratio * 0.1 * 1 + ratio * 0.3 * 10) / (500 / 0.75) + 0.5; 
//    ASSERT_TRUE(price == estimatedPrice);
//}

/*  In the following program, there are three classes, meal, food and ingredient.
    Meal contains a list(Vector) of food and its own name.
    Food contains the Recipie(which is a vector of pair contaning the ingredient and quantity of each ingredient) and its name
    Ingredient contains name of the ingredient.

    Meal_List is a vector containing all meals.
    Food_List is a vector containing all foods.
    Ingredient_List is a vector containing all ingredients.
*/

#include <iostream>
#include <vector>
#include <list>
#include <cctype>
#include <algorithm>
#include <string.h>

using namespace std;

// Forward declarations
class Ingredient;
class Food;
class Meal;

// Function prototypes
void properName(string &name);                              // Capitalize the first letter of each word and each letter after a space
vector<int> closestString(vector<string> l, string search); // Find closest strings to the search string
void displayIngredientList();                               // Display the list of ingredients
void displayFoodList();                                     // Display the list of foods
void displayMealList();                                     // Display the list of meals
Ingredient *searchIngredient(string Ingredient);            // Search for an ingredient from the list
Meal *searchMeal(string Meal);                              // Search for a meal from the list
Food *searchFood(string food);                              // Search for a food from the list
Ingredient *addIngredient(string ingre);                    // Add a new ingredient to the list
Meal *addMeal(string meal);                                 // Add a new meal to the list
Food *addFood(string food);                                 // Add a new food to the list
void removeFood();                                          // Remove a food from the list
void removeMeal();                                          // Remove a meal from the list
void removeIngredient();                                    // Remove an ingredient from the list
void displaySpecificMeal();                                 // Display a specific meal
void displaySpecificRecipe();                               // Display a specific recipe
void displayLine();                                         // Display a line separator

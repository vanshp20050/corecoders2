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


// Class declarations
class Ingredient
{
public:
    string name;
};

class Food
{
public:
    string name;
    vector<pair<Ingredient, int>> Recipe;

    void displayRecipe()
    {
        if (Recipe.size() == 0)
        {
            cout << "This recipe is empty" << endl;
        }
        for (int i = 0; i < Recipe.size(); ++i)
        {
            cout << Recipe[i].first.name << " : " << Recipe[i].second << endl;
        }
    }

    void modifyFood()
    {
        int choice = 0;

        string tmp_ing;
        Ingredient *newIngri = nullptr;

        while (true)
        {
            cout << "Enter 1 for displaying Recipe" << endl;
            cout << "Enter 2 to add ingredient" << endl;
            cout << "Enter 3 to remove ingredient" << endl;
            cout << "Enter any other number to exit" << endl;

            cin >> choice;
            cout << endl;
            cin.ignore();

            bool erased = 0;

            switch (choice)
            {
            case 1:
                displayRecipe();
                break;
            case 2:
                cout << "Enter name of ingredient" << endl;
                getline(cin, tmp_ing);
                properName(tmp_ing);
                newIngri = searchIngredient(tmp_ing);
                if (newIngri == nullptr)
                {
                    continue;
                }
                cout << endl
                     << "Specify amount of Ingredient: ";
                int amt;
                cin >> amt;
                Recipe.push_back(make_pair(*newIngri, amt));
                break;
            case 3:
                cout << "Enter name of ingredient" << endl;
                getline(cin, tmp_ing);
                properName(tmp_ing);

                for (int i = 0; i < Recipe.size(); i++)
                {
                    if (Recipe[i].first.name == tmp_ing)
                    {
                        Recipe.erase(Recipe.begin() + i);
                        erased = 1;
                        break;
                    }
                }
                if (erased)
                {
                    cout << "Entered ingredient doesn't exist in this recipe" << endl;
                }
                break;
            default:
                cout << "Following changes have been made to the recipe" << endl;
                displayRecipe();
                return;
            }
        }
    }
};

class Meal
{
public:
    vector<Food> meal;
    string name;

    void displayFood()
    {
        if (meal.size() == 0)
        {
            cout << "This Meal is empty" << endl;
        }
        for (int i = 0; i < meal.size(); ++i)
        {
            cout << meal[i].name << endl;
        }
    }

    void modifyMeal()
    {
        int choice = 0;

        string tmp_foo;
        Food *newfood = nullptr;

        while (true)
        {
            cout << "Enter 1 for displaying Food List" << endl;
            cout << "Enter 2 to add food" << endl;
            cout << "Enter 3 to remove food" << endl;
            cout << "Enter any other number to exit" << endl;

            cin >> choice;
            cout << endl;
            cin.ignore();

            bool erased = 0;

            switch (choice)
            {
            case 1:
                displayFood();
                break;
            case 2:
                cout << "Enter name of food" << endl;
                getline(cin, tmp_foo);
                properName(tmp_foo);
                newfood = searchFood(tmp_foo);
                if (newfood == nullptr)
                {
                    continue;
                }
                meal.push_back(*newfood);
                break;
            case 3:
                cout << "Enter name of food" << endl;
                getline(cin, tmp_foo);
                properName(tmp_foo);

                for (int i = 0; i < meal.size(); i++)
                {
                    if (meal[i].name == tmp_foo)
                    {
                        meal.erase(meal.begin() + i);
                        erased = 1;
                        break;
                    }
                }
                if (erased)
                {
                    cout << "Entered food doesn't exist in this meal" << endl;
                }
                break;
            default:
                cout << "Following changes have been made to the meal" << endl;
                displayFood();
                return;
            }
        }
    }
};

// Function definations
void displayLine()
{
    cout << endl;
    for (int i = 0; i < 50; i++)
    {
        cout << "--x";
    }
    cout << endl;
    cout << endl;
}

// Lists to store all the objects
vector<Food> Food_List;
vector<Ingredient> Ingredient_List;
vector<Meal> Meal_List;

void properName(string &name)
{
    name[0] = toupper(name[0]);
    for (int i = 1; i < name.size(); ++i)
    {
        if (name[i - 1] == ' ')
        {
            name[i] = toupper(name[i]);
        }
        else
        {
            name[i] = tolower(name[i]);
        }
    }
}

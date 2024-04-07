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


vector<int> closestString(vector<string> l, string search)
{
    vector<int> ans(min(5, (int)l.size()), -1);       // Stores position of each of the closest strings
    vector<int> char_diff(min(5, (int)l.size()), 26); // Stores the difference of charecter at the position where it occurs
    vector<int> char_pos(min(5, (int)l.size()), 0);   // Stores the position at which the strings differ

    for (int i = 0; i < l.size(); i++)
    {
        int pos, diff;
        for (int j = 0; j < min(l[i].length(), search.length()); j++)
        {
            if (l[i][j] != search[j])
            {
                pos = j;
                diff = abs(l[i][j] - search[j]);
                break;
            }
        }

        int max_diff = 0;
        int max_diff_pos;

        // Deciding whether to store the current position in the answer. If yes, storing it in place of the worst one.
        for (int k = 0; k < char_pos.size(); k++)
        {
            if (char_pos[k] == *min_element(char_pos.begin(), char_pos.end()) && char_diff[k] > max_diff)
            {
                max_diff = char_diff[k];
                max_diff_pos = k;
            }
        }

        if (pos == *min_element(char_pos.begin(), char_pos.end()))
        {
            if (diff < max_diff)
            {
                char_diff[max_diff_pos] = diff;
                char_pos[max_diff_pos] = pos;
                ans[max_diff_pos] = i;
                continue;
            }
        }

        if (pos > *min_element(char_pos.begin(), char_pos.end()))
        {
            char_diff[max_diff_pos] = diff;
            char_pos[max_diff_pos] = pos;
            ans[max_diff_pos] = i;
            continue;
        }
    }

    // Sorting the answer with respect to the difference in charecter position
    for (int i = 0; i < char_pos.size(); i++)
    {
        for (int j = i + 1; j < char_pos.size(); j++)
        {
            if (char_pos[i] < char_pos[j])
            {
                swap(char_pos[i], char_pos[j]);
                swap(ans[i], ans[j]);
            }
        }
    }

    return ans;
}

void displayIngredientList()
{
    if (Ingredient_List.empty())
    {
        cout << "There are no ingredients in the list" << endl;
        return;
    }
    cout << "Ingredient List:" << endl;
    for (int i = 0; i < Ingredient_List.size(); ++i)
    {
        cout << i + 1 << " : " << Ingredient_List[i].name << endl;
    }
}

void displayFoodList()
{
    if (Food_List.empty())
    {
        cout << "There are no foods in the list" << endl;
        return;
    }
    cout << "Food List:" << endl;
    for (int i = 0; i < Food_List.size(); ++i)
    {
        cout << i + 1 << " : " << Food_List[i].name << endl;
    }
}

void displayMealList()
{
    if (Meal_List.empty())
    {
        cout << "There are no meals in the list" << endl;
        return;
    }
    cout << "Meal List:" << endl;
    for (int i = 0; i < Meal_List.size(); ++i)
    {
        cout << i + 1 << " : " << Meal_List[i].name << endl;
    }
}

Ingredient *searchIngredient(string Ingredient)
{
    for (int i = 0; i < Ingredient_List.size(); ++i)
    {
        if (Ingredient_List[i].name == Ingredient)
        {
            return &Ingredient_List[i];
        }
    }

    vector<string> v(Ingredient_List.size());
    for (int b = 0; b < Ingredient_List.size(); b++)
    {
        v[b] = Ingredient_List[b].name;
    }
    vector<int> closest5 = closestString(v, Ingredient);

    cout << endl
         << "We couldn't find an exact match" << endl
         << "Closest " << closest5.size() << " searches are:" << endl;
    for (int b = 0; b < closest5.size(); b++)
    {
        cout << b + 1 << ":" << Ingredient_List[closest5[b]].name << endl;
    }
    int choice;
    cout << endl
         << "Enter the number corresponding to the most appropriate" << endl
         << "Enter 0 to add above entered ingredient to list" << endl
         << "Enter any other number to discard result" << endl;
    cin >> choice;
    cout << endl;
    cin.ignore();

    if (choice == 0)
    {
        return addIngredient(Ingredient);
    }
    if (choice <= closest5.size() && choice > 0)
    {
        return &Ingredient_List[closest5[choice - 1]];
    }
    return nullptr;
}

Meal *searchMeal(string Meal)
{
    for (int i = 0; i < Meal_List.size(); ++i)
    {
        if (Meal_List[i].name == Meal)
        {
            return &Meal_List[i];
        }
    }

    vector<string> v(Meal_List.size());
    for (int b = 0; b < Meal_List.size(); b++)
    {
        v[b] = Meal_List[b].name;
    }
    vector<int> closest5 = closestString(v, Meal);

    cout << endl
         << "We couldn't find an exact match" << endl
         << "Closest " << closest5.size() << " searches are:" << endl;
    for (int b = 0; b < closest5.size(); b++)
    {
        cout << b + 1 << ":" << Meal_List[closest5[b]].name << endl;
    }

    int choice;
    cout << endl
         << "Enter the number corresponding to the most appropriate" << endl
         << "Enter 0 to add above entered ingredient to list" << endl
         << "Enter any other number to discard result" << endl;

    cin >> choice;
    cout << endl;
    cin.ignore();

    if (choice == 0)
    {
        return addMeal(Meal);
    }

    if (choice <= closest5.size() && choice > 0)
    {
        return &Meal_List[closest5[choice - 1]];
    }
    return nullptr;
}

Food *searchFood(string food)
{
    properName(food);
    for (int i = 0; i < Food_List.size(); ++i)
    {
        if (Food_List[i].name == food)
        {
            return &Food_List[i];
        }
    }

    vector<string> v(Food_List.size());
    for (int b = 0; b < Food_List.size(); b++)
    {
        v[b] = Food_List[b].name;
    }
    vector<int> closest5 = closestString(v, food);

    cout << endl
         << "We couldn't find an exact match" << endl
         << "Closest " << closest5.size() << " searches are:" << endl;

    for (int b = 0; b < closest5.size(); b++)
    {
        cout << b + 1 << ":" << Food_List[closest5[b]].name << endl;
    }

    int choice;
    cout << endl
         << "Enter the number corresponding to the most appropriate" << endl
         << "Enter 0 to add above entered ingredient to list" << endl
         << "Enter any other number to discard result" << endl;

    cin >> choice;
    cout << endl;
    cin.ignore();

    if (choice == 0)
    {
        return addFood(food);
    }

    if (choice <= closest5.size() && choice > 0)
    {
        return &Food_List[closest5[choice - 1]];
    }
    return nullptr;
}

Ingredient *addIngredient(string ingre)
{
    properName(ingre);
    Ingredient *newIngredient = new Ingredient;
    newIngredient->name = ingre;
    Ingredient_List.push_back(*newIngredient);
    return newIngredient;
}

Meal *addMeal(string meal)
{
    properName(meal);
    Meal *newMeal = new Meal;
    newMeal->name = meal;
    cout << "Enter foods to add to the meal (enter 'done' to finish):" << endl;
    string foodName;

    while (true)
    {
        cout << endl
             << "Food name: ";
        getline(cin, foodName);

        properName(foodName);
        if (foodName == "Done")
        {
            break;
        }

        Food *newFood = searchFood(foodName);

        newMeal->meal.push_back(*newFood);
    }

    Meal_List.push_back(*newMeal);

    return newMeal;
}

Food *addFood(string food)
{
    properName(food);
    Food *newFood = new Food;
    newFood->name = food;

    cout << "Enter ingredients for the recipe (enter 'done' to finish):" << endl;
    while (true)
    {
        string ingredientName;
        int quantity;
        cout << endl
             << "Ingredient name: ";
        getline(cin, ingredientName);
        properName(ingredientName);

        if (ingredientName == "Done")
        {
            break;
        }

        Ingredient *newIngredient = searchIngredient(ingredientName);

        if (newIngredient == nullptr)
        {
            continue;
        }

        cout << "Quantity(in g): ";
        cin >> quantity;
        cin.ignore();

        newFood->Recipe.push_back({*newIngredient, quantity});
    }

    Food_List.push_back(*newFood);
    return newFood;
}

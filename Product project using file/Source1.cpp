#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

#pragma region "product" struct and global variables

struct product
{
	string name = "initial";
	long code = 12;
	double buying_cost = 13;
	double selling_price = 14;
	long quatity = 45;
	double discount = 57;
	double net_selling_price = 78;
	double profit = 78;
};

//Global variables
product* prod1 = NULL;//Watch out! Pointer that will refer to products array in this project are: prod, prod1 & prod2. 
string x;//It's used to read any string in the code.
long a;//It's used to read any int or long in the code.
double b;//It's used to read any double in the code.

#pragma endregion



#pragma region Products calculations functions 

double discount_funct(double selling_price)
{
	int percent;
	double discount = 0;
	string key;
	cout << "Enter the discount percent or to use the default discount percent (10%) press 'd' or to cancel the discount option" <<
		endl << "press 'e': ";
	cin >> key;
	if (key == "d")
		discount = (selling_price * 10) / 100;
	else if (key == "e")
		return discount;
	else
	{
		cout << "Verify the discount percent or change it : ";
		cin >> percent;
		while (percent < 0)
		{
			cout << "Renter a valid discount percent : ";
			cin >> percent;
		}
		discount = (selling_price * percent) / 100;
	}
	return discount;
}

double calculate_profit(double net_selling_price, double buying_cost, int quantity)
{
	double profit;
	profit = (net_selling_price - buying_cost) * quantity;
	return profit;
}

void max_profit(product* prod, int size)
{
	double max = prod[0].profit;
	int flag_1 = 0;
	for (int i = 1; i < size; i++)
	{
		if (max < prod[i].profit)
		{
			max = prod[i].profit;
			flag_1 = i;
		}
	}
	cout << "The maximum profit is " << prod[flag_1].profit << " out of the product of name '" << prod[flag_1].name
		<< "' and of code '" << prod[flag_1].code << "'." << endl << endl;
}

#pragma endregion



#pragma region Showing functions

void data_show(int i)
{
	cout << "\n The name of the product is : " << prod1[i].name;
	cout << "\n The code of the product is : " << prod1[i].code;
	cout << "\n The buying cost of the product is : " << prod1[i].buying_cost;
	cout << "\n The selling price of the product is : " << prod1[i].selling_price;
	cout << "\n The quatity of the product is : " << prod1[i].quatity;
	cout << "\n The discount of the product is : " << prod1[i].discount;
	cout << "\n The net selling price of the product is : " << prod1[i].net_selling_price;
	cout << "\n The profit of the product is : " << prod1[i].profit;
}

void data_file_show(product* prod, int size)
{
	ofstream products_file("productsDB.txt");
	products_file << "Used\n" << "Name                 : ";
	//writing the names
	for (int i = 0; i < size; i++)
	{
		products_file << prod[i].name << "          ";
	}
	products_file << "\nCode                 : ";
	//writing the codes
	for (int i = 0; i < size; i++)
	{
		products_file << prod[i].code << "            ";
	}
	products_file << "\nBuying costs         : ";
	//writing the buying costs
	for (int i = 0; i < size; i++)
	{
		products_file << prod[i].buying_cost << "            ";
	}
	products_file << "\nSelling prices       : ";
	//writing the selling prices
	for (int i = 0; i < size; i++)
	{
		products_file << prod[i].selling_price << "            ";
	}
	products_file << "\nQuantities           : ";
	//writing the quantities
	for (int i = 0; i < size; i++)
	{
		products_file << prod[i].quatity << "            ";
	}
	products_file << "\nDiscounts            : ";
	//writing the discounts
	for (int i = 0; i < size; i++)
	{
		products_file << prod[i].discount << "         ";
	}
	products_file << "\nNet selling prices   : ";
	//writing the net selling prices
	for (int i = 0; i < size; i++)
	{
		products_file << prod[i].net_selling_price << "         ";
	}
	products_file << "\nProfits              : ";
	//writing the profits
	for (int i = 0; i < size; i++)
	{
		products_file << prod[i].profit << "          ";
	}
}

#pragma endregion



#pragma region Data entry functions

void data_console_entry(string A, product* prod, int size)
{
	if (A == "all")
	{
		for (int i = 0; i < size; i++)
		{
			do 
			{
				cout << "\n\n(1)The name of the product number " << i + 1 << " is : ";
				cin >> prod[i].name;
				if (prod[i].name == "e")
					cout << "Invalid input. Choose any name either than 'e'.";
				else
					break;
			} while (true);

			do 
			{
			cout << "\n(2)The code of the product number " << i + 1 << " is : ";
			cin >> prod[i].code;
			if (prod[i].code == 0)
				cout << "Invalid input. Choose any code either than 0.\n";
			else
				break;
			} while (true);

			cout << "\n(3)The buying cost of the product number " << i + 1 << " is : ";
			cin >> prod[i].buying_cost;
			cout << "\n(4)The selling price of the product number " << i + 1 << " is : ";
			cin >> prod[i].selling_price;
			prod[i].discount = discount_funct(prod[i].selling_price);
			prod[i].net_selling_price = prod[i].selling_price - prod[i].discount;
			cout << "\n(5)The quantity of the product number " << i + 1 << " is : ";
			cin >> prod[i].quatity;
			prod[i].profit = calculate_profit(prod[i].net_selling_price, prod[i].buying_cost, prod[i].quatity);
		}
		data_file_show(prod, size);
		max_profit(prod, size);
	}
	else if (A == "part")
	{
		int num = 1;
		int size2 = size + a;
		for (; size < size2; size++)
		{
			cout << "\n\n(1)The name of the product number " << num << " to be added is : ";
			cin >> prod[size].name;
			cout << "\n(2)The code of the product number " << num << " to be added is : ";
			cin >> prod[size].code;
			cout << "\n(3)The buying cost of the product number " << num << " to be added is : ";
			cin >> prod[size].buying_cost;
			cout << "\n(4)The selling price of the product number " << num << " to be added is : ";
			cin >> prod[size].selling_price;
			prod[size].discount = discount_funct(prod[size].selling_price);
			prod[size].net_selling_price = prod[size].selling_price - prod[size].discount;
			cout << "\n(5)The quantity of the product number " << num << " to be added is : ";
			cin >> prod[size].quatity;
			prod[size].profit = calculate_profit(prod[size].net_selling_price, prod[size].buying_cost, prod[size].quatity);
			num++;
		}
		data_file_show(prod, size2);
		max_profit(prod, size2);
	}
}

void add_products(product* prod2, int size)
{
   int i;
   for(i = 0; i < size; i++)
   {
      prod2[i].name = prod1[i].name;
	  prod2[i].code = prod1[i].code;
	  prod2[i].buying_cost = prod1[i].buying_cost;
	  prod2[i].selling_price = prod1[i].selling_price;
	  prod2[i].quatity = prod1[i].quatity;
	  prod2[i].discount = prod1[i].discount;
	  prod2[i].net_selling_price = prod1[i].net_selling_price;
	  prod2[i].profit = prod1[i].profit;
   }
   data_console_entry("part", prod2, i);
}

void update_product(int i)
{
    int done = 0;
    string data;
	char flag = 's';
	cout << "Enter the number of the data that will be updated (Note: maximum number is 6 which are [ The list is :name , code,\n" 
	<< "buying_cost, selling_price, discount_percent and quantity]): ";
		cin >> a;
		cout << endl;
		for (int d = 1; d <= a; d++)
		{
			cout << "Choose the name of the data number '" << d << "' to be updated : ";
			cin >> data;
			if (data == "name")
			{
				cout << "Enter the new name : ";
				cin >> prod1[i].name;
				cout << endl;
			}
			else if (data == "code")
			{
				cout << "Enter the new code : ";
				cin >> prod1[i].code;
				cout << endl;
			}
			else if (data == "buying_cost")
			{
				cout << "Enter the new buying cost : ";
				cin >> prod1[i].buying_cost;
				cout << endl;
				done = 1;
			}
			else if (data == "selling_price")
			{
				goto before_discount;//before_discount is in the line number 275.
				before_discount://line 275.
				cout << "Enter the new selling price : ";
				cin >> prod1[i].selling_price;
				cout << endl;
				prod1[i].discount = discount_funct(prod1[i].selling_price);
				done = 1;
				if(flag == 'y')
					d++;
			}
			else if (data == "quantity")
			{
				cout << "Enter the new quantity : ";
				cin >> prod1[i].quatity;
				cout << endl;
				done = 1;
			}
			else if (data == "discount_percent")
			{

				cout << "Knowing that the selling price is ' " << prod1[i].selling_price << " '. If you intend to change the selling price nextly,"
					<< " you must change it now before the discount percent. Press 'y' to change the selling price and 'n' if you will never "
					<< "change it nextly: ";
				cin >> flag;
				do {
					if (flag == 'y')
					{
						goto before_discount;//before_discount is in the line number 275.
						break;
					}
					else if (flag == 'n')
					{
						prod1[i].discount = discount_funct(prod1[i].selling_price);
						done = 1;
						break;
					}
					else
					{
						cout << "Enter 'y' or 'n' only : ";
						cin >> flag;
					}
				} while (true);
			}
		}
		if (done == 1)
		{
			prod1[i].net_selling_price = prod1[i].selling_price - prod1[i].discount;
			prod1[i].profit = calculate_profit(prod1[i].net_selling_price, prod1[i].buying_cost, prod1[i].quatity);
		}
}

void deletion(product* prod2, int* indices, int size1, int size2, int size3)
{
	bool flage = false;
	int index = 0;
    for(int i = 0; i < size1; i++)
	{
		for(int j = 0; j < size3; j++)
		{
			if (indices[j] == i)
				break;
			if(j == (size2 - 1))
			{
				flage = true; 
				break;
			}
		}
		if (flage == true)
		{
			prod2[index].name = prod1[i].name;
			prod2[index].code = prod1[i].code;
			prod2[index].buying_cost = prod1[i].buying_cost;
			prod2[index].selling_price = prod1[i].selling_price;
			prod2[index].quatity = prod1[i].quatity;
			prod2[index].discount = prod1[i].discount;
			prod2[index].net_selling_price = prod1[i].net_selling_price;
			prod2[index].profit = prod1[i].profit;
			flage = false;
			index++;
		}
	}
	data_file_show(prod2, size2);
}

int size_finder(void)
{
	int size = 0;
	ifstream products_file("productsDB.txt");
	products_file >> x >> x >> x;
	for (int i = 0; true; i++)
	{
		products_file >> x;
		if (x == "Code")
			break;
		else
			size++;
	}
	products_file.close();
	return size;
}

void data_file_entry(string y, int& size)
{
	ifstream products_file("productsDB.txt");
	products_file >> x >> x >> x;
	if (y == "all")
	{
		size = size_finder();
	    prod1 = new product[size];
		//reading the names
		for (int i = 0; i < size; i++)
		{
			products_file >> x;
			prod1[i].name = x;
		}
		//reading the codes
		products_file >> x >> x;
		for (int i = 0; i < size; i++)
		{
			products_file >> a;
			prod1[i].code = a;
		}
		//reading the buying costs
		products_file >> x >> x >> x;
		for (int i = 0; i < size; i++)
		{
			products_file >> b;
			prod1[i].buying_cost = b;
		}
		//reading the selling prices
		products_file >> x >> x >> x;
		for (int i = 0; i < size; i++)
		{
			products_file >> b;
			prod1[i].selling_price = b;
		}
		//reading the quantities
		products_file >> x >> x;
		for (int i = 0; i < size; i++)
		{
			products_file >> a;
			prod1[i].quatity = a;
		}
		//reading the discount
		products_file >> x >> x;
		for (int i = 0; i < size; i++)
		{
			products_file >> b;
			prod1[i].discount = b;
		}
		//reading the net selling price
		products_file >> x >> x >> x >> x;
		for (int i = 0; i < size; i++)
		{
			products_file >> b;
			prod1[i].net_selling_price = b;
		}
		//reading the profits
		products_file >> x >> x;
		for (int i = 0; i < size; i++)
		{
			products_file >> b;
			prod1[i].profit = b;
		}
		products_file.close();
	}
}

#pragma endregion



#pragma region Searching functions

int search_code(int size, string B)
{
	bool flage = false;
	do 
	{
		cout << "\nEnter the code of the product that you want to (search for or upadte or delete it) or '0' to cancel : "; 
		cin >> a;
		if (a == 0)
			return -1;
		else
			break;
	} while (true);

	if (B == "all")
	{
		for (int i = 0; i < size; i++)
		{
			if (prod1[i].code == a)
			{
				data_show(i);
				flage = true;
				break;
			}
		}
	}

	else if (B == "part_update" || B == "part_deletion")
	{
		for (int i = 0; i < size; i++)
		{
			if (prod1[i].code == a)
				return i;
		}
	}

	if (flage == false)
		cout << "Not found\n";
	return -1;
}

int search_name(int size, string C)
{
	bool flage = false;
	do 
	{
		cout << "\nEnter the name of the product that you want to (search for or update or delete it) or 'e' to cancel : "; 
		cin >> x;
		if (x == "e")
			return -1;
		else 
			break;
	} while (true);

	if (C == "all")
	{
		for (int i = 0; i < size; i++)
		{
			if (prod1[i].name == x)
			{
				data_show(i);
				flage = true;
				break;
			}
		}
	}

	else if (C == "part_update" || C == "part_deletion")
	{
		for (int i = 0; i < size; i++)
		{
			if (prod1[i].name == x)
				return i;
		}
	}

	if (flage == false)
		cout << "Not found\n";
    return -1;
}

#pragma endregion



int main()
{
	char input_case;//It's used to read any single character.
	product* prod2 = NULL;//The pointer that is used in adding new products and deleting products.
	int size = 1;//The variable that holds the ACTUAL size of the prod1 only.
	cout << "*************************************************************************" << endl;
	cout << "                         Products project using file" << endl;
	cout << "*************************************************************************" << endl;
	ifstream products_file("productsDB.txt");
	goto first_use;//first_use is in the line number 123.
    first_use://line 123.
	products_file >> x;
	if (x != "Used")
	{
		products_file.close();
		cout << "\n\n It's your first use for the project.............Welcome ^_^\n\n";
		cout << "Then we will enter the information of the products.........\n\n";
		cout << "First enter the number of the products that you will enter their information : "; 
		cin >> size;
		prod1 = new product[size];
		data_console_entry("all", prod1, size);
	}
	else
	{
		products_file >> x;
		if (x != "Name")
		{
			do
			{
				cout << "The word 'Used' is written in the project file alone or there is a wrong organization for the file."
					<< "Bleach the 'productsDB' file to continue....Press 'e' if you end bleaching.\n";
				cin >> input_case; 
				if (input_case == 'e')
					goto first_use;//first_use is in the line number 123.
				else
					cout << "Invalid input\n";
			} while (true);
		}
		else
		{
			products_file.close();
	        data_file_entry("all", size);
		}
	}
	if(products_file.is_open())
	products_file.close();
	while (true)
	{
		cout << "\nEnter :\n(1)'n' to search for a product with the name or 'c' to search with the code.\n";
		cout << "(2)'a' to add products.\n";
		cout << "(3)'u' to update the date of any certain product.\n";
		cout << "(4)'d' to delete any number of products.\n";
		cout << "(5)'r' If you made changes[add, update or delete]in the file and want the program to re-read the file.\n";
		cout << "(6)'z' to get the total number of products you have.\n";
		cout << "(7)'m' to get the product with the maximum profit.\nYour input : ";
		cin >> input_case;
		switch (input_case)
		{
		case 'n':	
			search_name(size, "all");
			break;

		case 'c':
			search_code(size, "all");
			break;

		case 'a':
			cout << "\nEnter the number of the products that you will add or 'e' to cancel : "; 
			cin >> input_case;
			if (input_case == 'e')
				break;
			else 
			{
				cout << "\nVerify the number of the products that you will add (Enter '0' to cancel) : "; 
				cin >> a;
				if (a == 0) 
					break;
				else 
				{
					prod2 = new product[size + a];
					add_products(prod2, size);
					size += a;
					delete[] prod1;
					prod1 = new product[size];
					prod1 = prod2;
					prod2 = NULL;
					break;
				}
			}

		case 'u':
			do 
			{
				cout << "\nEnter 'n' to update with the name, 'c' to update with the code and 'e' to cancel : ";
				cin >> input_case;
				if(input_case == 'n')
				{ 
					a = search_name(size, "part_update");
					if (a != -1) 
					{
						update_product(a);
						max_profit(prod1, size);
						data_file_show(prod1, size);
						break;
					}
					else
						break;
				}
				else if(input_case == 'c')
				{
					a = search_code(size, "part_update");
					if (a != -1) 
					{
						update_product(a);
						max_profit(prod1, size);
						data_file_show(prod1, size);
						break;
					}
					else
						break;
				}
				else if(input_case == 'e')
					break;
				else
					cout << "Invalid input.\n";
			} while (true);
			break;

		case 'd':
			do 
			{
				cout << "\nEnter the number of products to be deleted or '0' to cancel : ";
				cin >> a;
				if (a > size)
					cout << "You cannot delete more than " << size << "product/s.\n";
				else if (a == 0)
					break;
				else
				{
					int* indices = new int[a];
					int index = 0;
					for (int i = 0; i < a;)
					{
						cout << "Product number " << i + 1 << ":.......Enter 'n' to delete with the name or 'c' to delete with the code : ";
						cin >> input_case;
						if (input_case == 'n')
						{
							index = search_name(size, "part_deletion");
							if (index == -1)
								continue;
							else
								indices[i] = index;
						}
						else if (input_case == 'c')
						{
							index = search_code(size, "part_deletion");
							if (index == -1)
								continue;
							else
								indices[i] = index;
						}
						i++;
					}
					prod2 = new product[size - a];
					deletion(prod2, indices, size, (size - a), a);
					size -= a;
					delete[] prod1;
					prod1 = new product[size];
					prod1 = prod2;
					prod2 = NULL;
					break;
				}
			} while (true);
			break;

		case 'r':
			data_file_entry("all", size);
			break;

		case 'z':
			cout << "\nThe number of products you have now is : " << size;
			break;

		case 'm':
			max_profit(prod1, size);
			break;

		default:
			cout << "\nInvalid input.";
			break;
		}
		cout << "\n***********************************************************************************\n";
	}
	delete [] prod1;
	return 0;
}
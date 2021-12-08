#include <bits/stdc++.h>
using namespace std;

// Class Begins Here

class restaurant
{

private:
    int itemno;
    char name[50];
    float price, qty;

public:
    void createmenu()
    {
        cout << "ENTER THE ITEM NUMBER:  " << endl;
        cin >> itemno;
        cout << "ENTER THE NAME OF THE DISH:  " << endl;
        gets(name);
        cout << "ENTER THE PRICE OF THE DISH:  " << endl;
        cin >> price;
    }

    void showmenu()
    {
        cout << "ITEM NUMBER:  " << itemno << endl;
        cout << "DISH:  " << name << endl;
        cout << "PRICE: " << price << endl;
    }

    int retitemno()
    {
        return itemno;
    }

    float retprice()
    {
        return price;
    }

    char *retname()
    {
        return name;
    }
};
// Class Ends Here

restaurant r;
fstream f;

// Function To Add Dish

void writemenu()
{
    f.open("rest.dat", ios::out | ios::app);
    r.createmenu();
    f.write((char *)&r, sizeof(restaurant));
    f.close();
    cout << "THE ITEM HAS BEEN ADDED ";
    //getch();
}
// Function To Display All Dishes

void displayall()
{
    system("CLS");
    cout << "        Menu" << endl;
    f.open("rest.dat", ios::in);

    while (f.read((char *)&r, sizeof(restaurant)))
    {
        r.showmenu();
        cout << endl
             << "====================================" << endl;
        //getch();
    }

    f.close();
    //getch();
}
// FUNCTION TO MODIFY

void modifyproduct()
{
    int no, found = 0;
    system("CLS");
    cout << "TO MODIFY:  ";
    cout << endl
         << "ENTER THE ITEM NUMBER: ";
    cin >> no;
    f.open("rest.dat", ios::in | ios::out);
    while (f.read((char *)&r, sizeof(restaurant)) && found == 0)
    {
        if (r.retitemno() == no)
        {
            r.showmenu();
            cout << "ENTER THE DETAILS OF THE NEW ITEM: ";
            r.createmenu();
            int pos = -1 * sizeof(restaurant);
            f.seekp(pos, ios::cur);
            f.write((char *)&r, sizeof(restaurant));
            cout << endl
                 << "ITEM IS UPDATED. ";
            found = 1;
        }
    }
    f.close();
    if (found == 0)
        cout << endl
             << endl
             << "ITEM NOT FOUND!!";
    //getch();
}

// FUNCTION TO DELETE PRODUCT

void deleteproduct()
{
    int no;
    system("CLS");
    cout << endl
         << endl
         << "  DELETE ITEM ";
    cout << "ENTER THE ITEM YOU WANT TO DELETE: ";
    cin >> no;
    f.open("rest.dat", ios::in | ios::out);
    fstream f2;
    f2.open("tempp.dat", ios::out);
    f.seekg(0, ios::beg);
    while (f.read((char *)&r, sizeof(restaurant)))
    {
        if (r.retitemno() != no)
        {
            f2.write((char *)&r, sizeof(r));
        }
    }
    f2.close();
    f.close();
    remove("rest.dat");
    rename("tempp.dat", "shop.dat");
    cout << endl
         << "RECORD DELETED. ";
    //getch();
}

// FUNCTION TO DISPLAY MENU
void menu()
{
    system("CLS");
    f.open("rest.dat", ios::in);
    if (!f)
    {
        cout << "ERROR! FILE CANNOT OPEN" << endl
             << "GO TO ADMIN MENU TO CREATE A FILE. ";
        cout << "PROGRAM IS NOW CLOSING";
        //getch();
        exit(0);
    }
    cout << endl
         << "        SKYDECK RESTAURANT MENU" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << setw(15) << " ITEM NO" << setw(15) << " NAME" << setw(15) << " PRICE" << endl;
    cout << "----------------------------------------------------";
    while (f.read((char *)&r, sizeof(restaurant)))
    {
        cout << endl
             << setw(13) << r.retitemno() << setw(15) << r.retname() << setw(15);
        cout << r.retprice() << endl;
    }
    f.close();
}

// Function To Place Order

void placeorder()
{
    int order[50], quan[50], c = 0;
    float amount, total = 0;
    char ch = 'y';
    menu();
    cout << endl
         << endl;
    cout << endl
         << "==================================";
    cout << endl
         << "         PLACE YOUR ORDER";
    cout << endl
         << "==================================" << endl;
    do
    {
        cout << "ENTER THE ITEM NUMBER:  ";
        cin >> order[c];
        cout << endl
             << "QUANTITY: ";
        cin >> quan[c];
        c++;
        cout << endl
             << "DO YOU WANT TO ORDER ANY OTHER ITEM ? (y/n)";
        cin >> ch;
    } while (ch == 'y');
    cout << endl
         << "THANK YOU FOR PLACING YOUR ORDER AT SKYDECK RESTAURANT ";
    //getch();
    system("CLS");
    cout << endl
         << "      --------------------------- INVOICE -----------------------" << endl
         << endl;
    cout << endl
         << setw(10) << "ITEM NO |" << setw(10) << "NAME  |" << setw(10) << "QUANTITY  |" << setw(10) << "PRICE  |" << setw(10) << "AMOUNT  " << setw(10) << endl;
    for (int x = 0; x <= c; x++)
    {
        f.open("rest.dat", ios::in);
        f.read((char *)&r, sizeof(restaurant));
        while (!f.eof())
        {
            if (r.retitemno() == order[x])
            {
                amount = r.retprice() * quan[x];
                cout << endl
                     << setw(10) << order[x];
                cout << setw(10) << r.retname();
                cout << setw(10) << quan[x] << r.retprice();
                cout << setw(10) << amount;
                total = total + amount;
            }
            f.read((char *)&r, sizeof(restaurant));
        }
        f.close();
    }
    cout << endl
         << endl
         << setw(25) << "TOTAL= " << total;
    //getch();
}

// Function To Introduce Programme Developer

void intro()
{
    system("CLS");
    cout << endl
         << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    cout << endl
         << "                        RESTAURANT MANAGAMENT SYSTEM";
    cout << endl
         << endl
         << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    cout << endl
         << endl
         << endl
         << endl
         << endl
         << "                                          MADE BY: Areeb Ahmad";
    //getch();
}

// Function For Admin

void adminmenu()
{
    system("CLS");
    char ch2;
    cout << endl
         << "********************************SKYDECK ADMIN MENU******************************";
    cout << endl
         << endl
         << "1.CREATE MENU" << endl
         << "2.MODIFY MENU" << endl
         << "3.DELETE MENU";
    cout << endl
         << "4.VIEW MENU" << endl
         << "5.BACK TO MAIN MENU";
    ch2 = getchar();
    switch (ch2)
    {
    case '1':
        system("CLS");
        writemenu();
        break;

    case '2':
        modifyproduct();
        break;

    case '3':
        deleteproduct();
        break;

    case '4':
        menu();
        //getch();
        break;

    case '5':
        goto func;
        break;

    default:
        cout << "\a";
        adminmenu();
    }
}

// Main Function Starts Here

int main()
{
    func:
    system("CLS");

    cout << "*************************  DATABASE MANAGEMENT SYSTEM  *************************" << endl;

    char ch;
    intro();
    do
    {
        system("CLS");
        cout << endl
             << "*****************************SKYDECK MAIN MENU**********************************";
        cout << endl
             << "1.CUSTOMER";
        cout << endl
             << "2.ADMINISTRATOR";
        cout << endl
             << "3.EXIT";
        ch = getchar();

        switch (ch)
        {
        case '1':
            system("CLS");
            placeorder();
            //getch();
            break;

        case '2':
            adminmenu();
            break;

        case '3':
            exit(0);

        default:
            cout << "\a";
        }
    } while (ch != '3');

    return 0;
}

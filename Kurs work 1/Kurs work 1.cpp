#include <iostream>
#include <iomanip>
#include <locale.h>
#include <windows.h>
#include <fstream>
#include <stdio.h >

using namespace std;

struct vedomost
{
    int t_number, // Табельный номер
        t_rate, // тарифная ставка в час
        fact_h, //фактически отработанные часы
        t_category, // тарифный розряд
        final_earn, // итоговый зароботок
        sum_of_fact_h, // сумма отработанных часов
        sum_of_final_earn; // сумма итоговово заработка
    double tr = 1; // переменная для подсчёта коефициента прибавки тарифного розряда
};

vedomost c[10];
vedomost b;

int fill_mass()  // заповнення масиву даними з клавіатури
{
    int n;//тимчасова змінна для того, щоб повернути у голову програму введену кількість
    cout << "\n Введіть кількість робітників <10 : "; cin >> n;
    cout << "\n Введіть данні для відомості : \n ";
    

    for (int i = 0; i < n; i++)
    {
        cout << "\n Введіть для " << i + 1 << " робітника : ";
        cout << "\n Введіть Табельний номер: "; cin >> c[i].t_number;
        cout << "\n Введіть Тарифну ставку години, грн : "; cin >> c[i].t_rate;

        cout << "\n Введіть фактично відпрацьований час: "; cin >> c[i].fact_h;
        cout << "\n Введіть тарифний розряд : "; cin >> c[i].t_category;
        if (c[i].t_category == 5)
        {
            c[i].tr = 1.15;
        }
        else if (c[i].t_category == 6)
        {
            c[i].tr = 1.55;
        }
        else if (c[i].t_category == 6)
        {
            c[i].tr = 2.5;
        }
        c[i].final_earn = c[i].t_rate * c[i].fact_h * c[i].tr;
        b.sum_of_fact_h += c[i].fact_h;
        b.sum_of_final_earn += c[i].final_earn;  
            }
    cout << "\n Дані введені!!" << endl;
    return n;
};

void show(int v) // виведення на екран
{
    if (!v)
    {
        cout << "У массиві немає даних" << endl; return;
    }
    else
    {
        // шапка таблицы
        cout << "__________________________________________________________________________________________________________________________________________________" << endl;
        cout << setw(8) << "No п/п" << setw(20) << " Табельний номер"
            << setw(32) << "Тарифна ставка години, грн." << setw(38) << "Фактично відпрацьований час, год."
            << setw(20) << "Тарифний розряд" << setw(26) << " Заробітна плата, грн." << endl;
        cout << "__________________________________________________________________________________________________________________________________________________" << endl;
        //виведення рядків таблиці
        for (int i = 0; i < v; i++)
        {
        cout << setw(5) << i + 1 << setw(15) << c[i].t_number
                << setw(32) << c[i].t_rate << setw(35) << c[i].fact_h
                << setw(23) << c[i].t_category << setw(26) << c[i].final_earn << endl;

        cout << "__________________________________________________________________________________________________________________________________________________" << endl;
        }
        // Вывод "Всего"
        cout << setw(23) << "Усього" << setw(65) << b.sum_of_fact_h << setw(48) << b.sum_of_final_earn << endl;
        cout << "__________________________________________________________________________________________________________________________________________________" << endl;
    }
}



int fill_file(int q)//q- кількість рядків масиву, функція запису даних у файл
{
    ofstream f;
    setlocale(LC_ALL, "rus");
    char name[12];
    cout << "\n Введіть ім’я файлу: "; cin >> name;
    f.open(name);
    if (!f)
    {
        cout << "\n Error"; getchar();
    }
    for (int i = 0; i < q; i++)
    {
        f  << " " << c[i].t_number << " " << c[i].t_rate << " " << c[i].fact_h << " "
            << c[i].t_category << " " << c[i].final_earn << " " << b.sum_of_fact_h << " " << b.sum_of_final_earn << endl;
    }
    f.close();
    cout << "Дані були записані у файл " << name << endl;
    return q;
}   


int read() // читання даних із файлу
{
    int i = 0; 
    char name[12]; 
    cout << "\nВведите имя файла: "; cin >> name;
    ifstream read_f; //оголошення файлової змінної
    read_f.open(name); //відкрити файл для читання даних
    if (!read_f) cout << "\nПомилка відкриття файлу!" << endl;
    else
    {
        while (1)//безкінечний цикл
        {
            if (read_f.tellg() == -1) break;//якщо вказівник вийшов за межі файлу – вийти з циклу
            //читання із файлу
            read_f >> c[i].t_number >> c[i].t_rate >> c[i].fact_h >> c[i].t_category >> c[i].final_earn >> b.sum_of_fact_h >> b.sum_of_final_earn;
            i++;
        }
        cout << "\nДані прочитані із файлу " << name << " успішно. " << endl;
        //обчислюються потрібні поля
       
    }
    return i - 1;
}

void edit(int v) // редагування
{
        int kol_strok = v;
        int line;// порядковий номер рядка для зміни даних
        int column;// порядковий номер поля
        if (kol_strok > 0)//якщо масив даних не пустий
        {
            cout << "\nВведіть порядковий номер рядка: "; cin >> line;
            line--;
            cout << "\nВведіть номер поля: \n";
            cout << "\nТабельний номер-1";
            cout << "\nТарифна ставка години -2 ";
            cout << "\nФактично відпрацьований час Т-3 ";
            cout << "\nТарифний розряд-4 \n";
            cin >> column;
            cout << "\n Введіть нове значення для поля \n" << endl;
            switch (column)
            {
            case 1: { cin >> c[line].t_number; } break;
            case 2: { cin >> c[line].t_rate; } break;
            case 3: { cin >> c[line].fact_h; } break;
            case 4: { cin >> c[line].t_category; } break;
            default: {cout << "\nНeмає такого поля\n"; column = 0; }
            }
            if (column != 0) cout << "\nЗміни внесені\n";
            if (c[line].t_category == 5)
            {
                c[line].tr = 1.15;
            }
            else if (c[line].t_category == 6)
            {
                c[line].tr = 1.55;
            }
            else if (c[line].t_category == 6)
            {
                c[line].tr = 2.5;
            }
            c[line].final_earn = c[line].t_rate * c[line].fact_h * c[line].tr;
            b.sum_of_fact_h = 0;
            b.sum_of_final_earn = 0;
            //після зміни значень полів очистити змінні сум
            //перерахунок значень змінних сум
            for (int i = 0; i < v; i++)
            {
                b.sum_of_fact_h += c[i].fact_h;
                b.sum_of_final_earn += c[i].final_earn;
            }
        }
}


int main()
{
       
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int chose, //выбор действия пользователя
    v = 0; // переменная для збережения количества записей в массив ведомости
    cout << "КУРСОВА РОБОТА" << endl;
    cout << "Системне Програмування" << endl;
    cout << "студента групи Е-74" << endl;
    cout << "Єрьоменка Дмитра " << endl;
    cout << "Варіант No 3" << endl;

    do
    {
        cout << "\nДля заповнення таблиці даними з клавіатури введіть 1: " << endl;
        cout << "Для виведення на екран введіть 2: " << endl;
        cout << "Для запису даних у файл введіть 3: " << endl;
        cout << "Для читання даних із файлу введіть 4: " << endl;
        cout << "Для редагування введіть 5: " << endl;
        cout << "Для виходу з програми введіть 0: " << endl;
        cin >> chose;
        switch (chose)
        {
        case 1: v = fill_mass(); break;
        case 2: show(v); break;
        case 3: fill_file(v); break;
        case 4: v = read(); break;
        case 5: edit(v); break;
        case 0: break;
        default:cout << "Неправильний вибір";
        }
    } while (chose != 0);

    return 0;
}


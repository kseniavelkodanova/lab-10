#include <iostream>
#include <cmath>

using namespace std;

/*==================================================================*/
/*                             TASK 1                               */
/*==================================================================*/
struct TTime {
    int Hour;  // 0‒23
    int Min;   // 0‒59
    int Sec;   // 0‒59
};

/*— перевірка коректності часу —*/
bool IsValidTime (const TTime& t)
{
    return (t.Hour>=0 && t.Hour<24) &&
           (t.Min >=0 && t.Min <60) &&
           (t.Sec >=0 && t.Sec <60);
}

/*— додаємо одну секунду, якщо час коректний —*/
void NextSec (TTime& t)
{
    if (!IsValidTime(t)) return;

    ++t.Sec;
    if (t.Sec==60) {
        t.Sec = 0;
        ++t.Min;
        if (t.Min==60) {
            t.Min = 0;
            ++t.Hour;
            if (t.Hour==24) t.Hour = 0;
        }
    }
}

/*==================================================================*/
/*                        TASK 2  (two subtasks)                    */
/*==================================================================*/

/*----------- 2.1  Відрізки на числовій осі  -----------------------*/
struct SegmentsData {
    double A{}, B{}, C{};
    double AC{}, BC{}, sum{};
};

/*— введення та перевірка —*/
void ReadSegmentsData (SegmentsData& d)
{
    cout << "\n[2.1] Введіть три точки A, B, C: ";
    cin  >> d.A >> d.B >> d.C;
    // коректність тут формально не обмежується: дійсні числа дозволені
}

/*— обробка —*/
void SolveSegments (SegmentsData& d)
{
    d.AC  = fabs(d.C - d.A);
    d.BC  = fabs(d.C - d.B);
    d.sum = d.AC + d.BC;
}

/*----------- 2.2  Тризначне число: зростання/спадання ------------*/
struct NumberData {
    int  num{};
    bool monotonic{};   // істинність висловлювання
};

/*— введення з перевіркою на тризначність —*/
void ReadNumberData (NumberData& d)
{
    do {
        cout << "\n[2.2] Введіть тризначне число: ";
        cin  >> d.num;
    } while (abs(d.num) < 100 || abs(d.num) > 999);
}

/*— обробка —*/
void CheckMonotonic (NumberData& d)
{
    int n = abs(d.num);
    int c =  n % 10;   n /= 10;
    int b =  n % 10;   n /= 10;
    int a =  n % 10;

    d.monotonic = (a < b && b < c) || (a > b && b > c);
}

/*==================================================================*/
/*                               MAIN                               */
/*==================================================================*/
int main()
{
    /*---------------------   TASK 1 tests   -----------------------*/
    cout << "==========  TASK 1: NextSec  ==========\n";
    for (int i=1;i<=5;++i)
    {
        TTime t;
        cout << "Час #" << i << " (год хв сек): ";
        cin  >> t.Hour >> t.Min >> t.Sec;

        cout << "  Вхідні дані: ";
        if (IsValidTime(t))
            cout << t.Hour << ':' << t.Min << ':' << t.Sec << '\n';
        else
            cout << "(некоректний час)\n";

        NextSec(t);

        cout << "  Після NextSec: ";
        if (IsValidTime(t))
            cout << t.Hour << ':' << t.Min << ':' << t.Sec << "\n\n";
        else
            cout << "(час не змінено, був некоректний)\n\n";
    }

    /*---------------------   TASK 2.1   ---------------------------*/
    SegmentsData seg;
    ReadSegmentsData(seg);
    SolveSegments(seg);
    cout << "\n==========  TASK 2.1: Segments  ==========\n";
    cout << "AC = "   << seg.AC  << "\n"
         << "BC = "   << seg.BC  << "\n"
         << "AC+BC = "<< seg.sum << "\n";

    /*---------------------   TASK 2.2   ---------------------------*/
    NumberData nd;
    ReadNumberData(nd);
    CheckMonotonic(nd);
    cout << "\n==========  TASK 2.2: Number  ==========\n";
    cout << "Цифри числа " << nd.num
         << (nd.monotonic ? " дійсно " : " не ")
         << "утворюють зростаючу або спадаючу послідовність.\n";

    cout << "\n***  Програма завершила роботу  ***\n";
    return 0;
}

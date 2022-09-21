/* Вариант 9 (10 баллов) Разработайте иерархию классов Суп → (Борщ, Тыквенный суп),
ВтороеБлюдо → (ЖаренаяКартошка, Котлета). При помощи паттерна AbstractFactory
разработайте классы Диета → (МяснаяДиета, ВегетарианскаяДиета). Продемонстрируйте
работу паттерна.
Доп. задания:
(5 баллов) Добавьте в этот паттерн новое блюдо — десерт. Внесите необходимые изменения
в код, продемонстрируйте работу паттерна
(5 баллов) Добавьте в этот паттерн новую диету - кефирную (первым блюдом для нее будет
окрошка, вторым — пудинг, третьим — мороженое или йогурт). */
//x/

#include <iostream>
#include <Windows.h>
using namespace std;


/// Абстрактные продукты ///
// Суп
class Soup {
public:
    virtual void prepare() = 0; // ЧВФ ( функция с заголовком но без чистой реализации 
};

// ВтороеБлюдо
class SecondCourse {
public:
    virtual void prepare() = 0;
};

// Десерт 
class Dessert {
public:
    virtual void prepare() = 0;
};


/// Конкретные продукты ///
// Борщ
class Borsch : public Soup {//все являются наследниками 
public:
    virtual void prepare() {//переопределение виртуального метода готовки 
        cout << "Пригтовить борщ" << endl;
    }
};

// Тыквенный суп
class PumpkinSoup : public Soup {
public:
    virtual void prepare() {
        cout << "Приготовить тыквенный суп" << endl;
    }
};

// Котлета
class Cutlet : public SecondCourse {
public:
    virtual void prepare() {
        cout << "Приготовить котлету" << endl;
    }
};

// Жареная картошка
class FriedPotato : public SecondCourse {
public:
    virtual void prepare() {
        cout << "Приготовить жареную картошку" << endl;
    }
};

// Мясной пирог
class MeatPie : public Dessert {
public:
    virtual void prepare() {
        cout << "Приготовить мясной пирог" << endl;
    }
};

// Мороженое пломбир
class IceCreamSundae : public Dessert {
public:
    virtual void prepare() {
        cout << "Приготовить мороженое пломбир" << endl;
    }
};


// Для еще одного уровень сложности нужна конкретная фабрика + семейство конкретных продуктов
// Новое семейство конкретных продуктов
// Окрошка
class Okroshka : public Soup {
public:
    void prepare() {
        cout << "Приготовить окрошку" << endl;
    }
};

// Пудинг
class Pudding : public SecondCourse {
public:
    void prepare() {
        cout << "Приготовить пудинг" << endl;
    }
};

// Йогурт
class Yogurt : public Dessert {
public:
    void prepare() {
        cout << "Приготовить йогурт" << endl;
    }
};


/// Абстрактная фабрика (задача абстрактной фабрики дать некоторый интерфейс, чтобы создавать семейство продуктов) ///
class AbstractFactoryDiet {
public:
    virtual Soup* createSoup() = 0; // интерфейс для создания семейств объектов - супов
    virtual SecondCourse* createSecondCourse() = 0; // интерфейс для создания семейств объектов - вторых блюд
    virtual Dessert* createDessert() = 0; // интерфейс для создания семейств объектов - десертов
};


/// Конкретные фабрики ///
// Мясная диета
//создаём экземпляры для определённого семейста, в данном случае - мясная деита 
class MeatDiet : public AbstractFactoryDiet {
    virtual Soup* createSoup() {//переопределяем конкретные продукты
        return new Borsch();
    }
    virtual SecondCourse* createSecondCourse() {
        return new Cutlet();
    }
    virtual Dessert* createDessert() {
        return new MeatPie();
    }
};

// Вегетарианская диета
class VegetarianDiet : public AbstractFactoryDiet {
    virtual Soup* createSoup() {
        return new PumpkinSoup();
    }
    virtual SecondCourse* createSecondCourse() {
        return new FriedPotato();
    }
    virtual Dessert* createDessert() {
        return new IceCreamSundae();
    }
};


// Добавляем еще одну конкретную диету - кефирную, если уже добавили семейство продуктов
struct KefirDiet : public AbstractFactoryDiet {
    Soup* createSoup() {
        return new Okroshka();
    }
    SecondCourse* createSecondCourse() {
        return new Pudding();
    }
    Dessert* createDessert() {
        return new Yogurt();
    }
};


// Программа-клиент
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Первая фабрика - Вегетарианская диета
    AbstractFactoryDiet* F = new VegetarianDiet();//указатель на абстрактную фабрику F. и помещаем в неё конкретную фабрику
    Soup* firs_course;
    SecondCourse* second_course;
    Dessert* third_course;

    cout << "Вегетарианская диета:" << endl;
    firs_course = F->createSoup();//вызываем фабрику и используем её методы 
    second_course = F->createSecondCourse();
    third_course = F->createDessert();

    firs_course->prepare();//приготовим конкретные блюда 
    second_course->prepare();
    third_course->prepare();

    delete F;
    delete firs_course; delete second_course; delete third_course;

    // конкретная фабрика несёт за собой смену семейства продуктов 
        // Вторая фабрика - Мясная диета
    F = new MeatDiet();

    cout << endl << endl << "Мясная диета:" << endl;
    firs_course = F->createSoup();
    second_course = F->createSecondCourse();
    third_course = F->createDessert();

    firs_course->prepare();
    second_course->prepare();
    third_course->prepare();

    delete F;
    delete firs_course; delete second_course; delete third_course;


    // Третья фабрика - Кефирная диета
    F = new KefirDiet();

    cout << endl << endl << "Кефирная диета:" << endl;
    firs_course = F->createSoup();
    second_course = F->createSecondCourse();
    third_course = F->createDessert();

    firs_course->prepare();
    second_course->prepare();
    third_course->prepare();

    delete F;
    delete firs_course; delete second_course; delete third_course;

    return 0;
}

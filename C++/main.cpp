#include "myset.hpp"
#include <cassert>
#include <iostream>
#include <string>
#include "person.h"
#include <stdexcept>

/**
 * @brief Functor used for testing MySet class with int types
 * 
 * This struct allows to check if two int types are equals or not.
**/
struct equal_int {

    /** 
    * @brief Round bracket operator
    * 
    * @param a First int number.
    * @param b Second int number.
    * @return True if a and b are equals, otherwise false.
    **/ 
    bool operator()(int a, int b) const {
        return a == b;
    }
};

/**
* @brief Functor used for testing filter_out method contained in MySet class with int types.
* 
* This struct allows to check if an int number is odd.
**/ 
struct is_odd {

    /**
    * @brief Round bracket operator
    * 
    * @param a Int number.
    * @return True if a is odd, otherwise false.
    **/ 
    bool operator()(int a) const {
        return a % 2 != 0;
    }
};

/**
 * @brief Functor used for testing MySet class with std::string types.
 * 
 * This struct allows to check if two std::string types are equals or not.
**/
struct equal_string {

    /**
    * @brief Round bracket operator
    * 
    * @param a Const reference to the first std::string.
    * @param b Const reference to the second std::string.
    * @return True if std::string a and std::string b are equals, otherwise false.
    **/ 
    bool operator()(const std::string& a, const std::string& b) const {
        return a.compare(b) == 0;
    }
};

/**
* @brief Functor used for testing filter_out method contained in MySet class with std::string types.
* 
* This struct allows to check if a std::string has even length.
**/ 
struct even_length {

    /**
    * @brief Round bracket operator
    * 
    * @param a Const reference to a std::string.
    * @return True if std::string has an even length, otherwise false.
    **/ 
    bool operator()(const std::string& s) const {
        return s.length() % 2 == 0;
    }
};

/**
 * @brief Functor used for testing MySet class with custom types.
 * 
 * This struct allows to check if two Person types are equals or not.
**/
struct equal_person {

    /**
    * @brief Round bracket operator
    * 
    * @param a Const reference to the first Person.
    * @param b Const reference to the second Person.
    * @return True if Person a and Person b are equals, otherwise false.
    **/ 
    bool operator()(const Person& a, const Person& b) const {
        return a == b;
    }
};

/**
 * @brief Functor used for testing filter_out method contained in MySet class with Person types.
 * 
 * This struct allows to check if a Person is more then 25 years old.
**/
struct is_over_25{

    /**
    * @brief Round bracket operator
    * 
    * @param a Reference to a Person.
    * @return True if Person a is more then 25 years old, otherwise false.
    **/ 
    bool operator()(const Person& a) const {
        return a._age > 25;
    }
};

typedef MySet<int, equal_int> MySetInt;
typedef MySet<std::string, equal_string> MySetString;
typedef MySet<Person, equal_person> MySetPerson;

MySetInt mySetInt(int startPoint) {
    MySetInt s;
    for(unsigned int i = 0; i < 10; ++i)
        s.add(startPoint++);
    return s;
}

MySetString mySetString() {
    MySetString s;
    s.add("claudio");
    s.add("simone");
    s.add("stefano");
    s.add("alessandro");
    s.add("matteo");
    s.add("andrea");
    s.add("daniela");
    s.add("cristina");
    s.add("burt");
    s.add("gaia");
    return s;
}

MySetPerson mySetPerson() {
    MySetPerson s;
    s.add(Person("claudio", "rota", 26));
    s.add(Person("simone", "mottadelli", 22));
    s.add(Person("alessandro", "sorrentino", 21));
    s.add(Person("matteo", "paolella", 23));
    s.add(Person("stefano", "zuccarella", 21));
    s.add(Person("burt", "ratti", 25));
    s.add(Person("andrea", "malerba", 21));
    s.add(Person("nicoletta", "mazzoleni", 52));
    s.add(Person("martina", "nava", 25));
    s.add(Person("andrea", "milani", 23));
    return s;
}

void testInt() {
    std::cout << "**********testInt : BEGIN**********" << std::endl;
    MySetInt s = mySetInt(0);

    // SIZE
    assert(s.size() == 10);
    std::cout << "testInt : size - OK" << std::endl;

    // DEFAULT CONSTRUCTOR
    MySetInt msi;
    assert(msi.size() == 0);
    std::cout << "testInt : default construtor - OK" << std::endl;

    // COPY CONSTRUCTOR
    MySetInt msi1(s);
    assert(msi1.size() == 10);
    assert(msi1[0] == 0);
    assert(msi1[7] == 7);
    assert(msi1[9] == 9);
    std::cout << "textInt : copy costructor - OK" << std::endl;

    // CONSTRUCTOR WITH ITERATORS
    MySetInt::const_iterator b = s.begin(), e = s.end();
    MySetInt msi5(b, e);
    assert(msi5.size() == 10);
    assert(msi5[3] == 3);
    assert(msi5[0] == 0);
    assert(msi5[7] != 8);
    assert(msi5[2] == 2);
    assert(msi5[9] == 9);
    std::cout << "textInt : constructor with iterators - OK" << std::endl;

    // OPERATOR=
    MySetInt msi2 = s;
    assert(msi2.size() == 10);
    assert(msi2[0] == 0);
    assert(msi2[3] == 3);
    assert(msi2[9] == 9);
    std::cout << "textInt : operator= - OK" << std::endl;

    // OPERATOR[]
    assert(msi2[0] == 0);
    assert(msi2[3] != 4);
    assert(msi2[3] == 3);
    assert(msi2[9] == 9);
    std::cout << "textInt : operator[] - OK" << std::endl;


    // ADD
    MySetInt msi3(s);
    // addition of an element that already exists
    // in the middle
    try {
        msi3.add(4);
        assert(false);

    }
    catch(const std::runtime_error& error){}
    // ahead
    try {
        msi3.add(0);
        assert(false);

    }
    catch(const std::runtime_error& error){}
    // at the end
    try {
        msi3.add(4);
        assert(false);

    }
    catch(const std::runtime_error& error){}

    // addition of new element that doesn't exist
    msi3.add(10);
    assert(msi3.size() == 11);
    assert(msi3[10] == 10);
    msi3.add(13);
    assert(msi3.size() == 12);
    assert(msi3[11] == 13);
    std::cout << "testInt : add - OK" << std::endl;

    // REMOVE
    MySetInt msi4(s);
    // removal of an existing element
    // at the end
    msi4.remove(9);
    assert(msi4.size() == 9);
    assert(msi4[8] == 8);
    msi4.remove(8);
    assert(msi4.size() == 8);
    assert(msi4[7] == 7);
    // ahead
    msi4.remove(0);
    assert(msi4.size() == 7);
    assert(msi4[0] == 1);
    msi4.remove(1);
    assert(msi4.size() == 6);
    assert(msi4[0] == 2);
    assert(msi4[1] == 3);
    // in the middle
    msi4.remove(4);
    assert(msi4.size() == 5);
    assert(msi4[4] == 7);
    msi4.remove(6);
    assert(msi4.size() == 4);
    assert(msi4[3] == 7);
    // removal of  an element that doesn't exist
    try {
        msi4.remove(0);
        assert(false);
    }
    catch(const std::runtime_error& error) {}
    try {
        msi4.remove(4);
        assert(false);
    }
    catch(const std::runtime_error& error) {}
    try {
        msi4.remove(9);
        assert(false);
    }
    catch(const std::runtime_error& error) {}
    std::cout << "testInt : remove - OK" << std::endl;

    // OPERATOR<<
    std::cout << s << std::endl;
    std::cout << "testInt : operator<< - OK" << std::endl;
    std::cout << "**********testInt : END**********";
}

void testPerson() {
    MySetPerson s = mySetPerson();
    equal_person ep;

    std::cout << "**********testPerson : BEGIN**********" << std::endl;

    // SIZE
    assert(s.size() == 10);
    std::cout << "testPerson : size - OK" << std::endl;

    // DEFAULT CONSTRUCTOR
    MySetPerson msp;
    assert(msp.size() == 0);
    std::cout << "testPerson : default construtor - OK" << std::endl;

    // COPY CONSTRUCTOR
    MySetPerson msp1(s);
    assert(msp1.size() == 10);
    assert(ep(msp1[7], Person("nicoletta", "mazzoleni", 52)));
    assert(ep(msp1[0], Person("claudio", "rota", 26)));
    assert(ep(msp1[3], Person("matteo", "paolella", 23)));
    assert(ep(msp1[9], Person("andrea", "milani", 23)));
    std::cout << "testPerson : copy construtor - OK" << std::endl;

    // OPERATOR=
    MySetPerson msp2 = msp1;
    assert(msp2.size() == 10);
    assert(ep(msp2[3], Person("matteo", "paolella", 23)));
    assert(ep(msp2[0], Person("claudio", "rota", 26)));
    assert(ep(msp2[9], Person("andrea", "milani", 23)));
    assert(ep(msp2[5], Person("burt", "ratti", 25)));
    std::cout << "testPerson : operator= - OK" << std::endl;

    // OPERATOR[]
    assert(ep(msp2[0], Person("claudio", "rota", 26)));
    assert(!ep(msp2[3], Person("alessandro", "sorrentino", 21)));
    assert(ep(msp2[2], Person("alessandro", "sorrentino", 21)));
    assert(ep(msp2[6], Person("andrea", "malerba", 21)));
    assert(ep(msp2[9], Person("andrea", "milani", 23)));
    std::cout << "testPerson : operator[] - OK" << std::endl;

    // CONSTRUCTOR WITH ITERATOR
    MySetPerson::const_iterator b = s.begin(), e = s.end();
    MySetPerson msp3(b, e);
    assert(msp3.size() == 10);
    assert(ep(msp3[1], Person("simone", "mottadelli", 22)));
    assert(ep(msp3[9], Person("andrea", "milani", 23)));
    assert(ep(msp3[3], Person("matteo", "paolella", 23)));
    assert(ep(msp3[0], Person("claudio", "rota", 26)));
    std::cout << "testPerson : constructor with iterators - OK" << std::endl;

    // ADD
    MySetPerson msp4(s);
    // addition of an element that already exists
    // in the middle
    try {
        msp4.add(Person("nicoletta", "mazzoleni", 52));
        assert(false);
    }
    catch(const std::runtime_error& error) {}
    // ahead
    try {
        msp4.add(Person("claudio", "rota", 26));
        assert(false);
    }
    catch(const std::runtime_error& error) {}
    // at the end
    try {
        msp4.add(Person("andrea", "milani", 23));
        assert(false);
    }
    catch(const std::runtime_error& error) {}
    // addition of new element that doesn't exist
    msp4.add(Person("claudio", "rota", 40));
    assert(msp4.size() == 11);
    assert(ep(msp4[10], Person("claudio", "rota", 40)));
    msp4.add(Person("giacomina", "rota", 63));
    msp4.add(Person("roberto", "sorrentino", 21));
     assert(ep(msp4[11], Person("giacomina", "rota", 63)));
    assert(msp4.size() == 13);
    msp4.add(Person("simone", "mottadelli", 23));
    assert(msp4.size() == 14);
    msp4.add(Person("burt", "arrigo", 25));
    assert(ep(msp4[14], Person("burt", "arrigo", 25)));
    assert(msp4.size() == 15);
    std::cout << "testString : add - OK" << std::endl;

    // REMOVE
    MySetPerson msp5(s);
    // removal of an existing element
    // at the end
    msp5.remove(Person("andrea", "milani", 23));
    assert(msp5.size() == 9);
     assert(ep(msp5[8], Person("martina", "nava", 25)));
    msp5.remove(Person("martina", "nava", 25));
    assert(msp5.size() == 8);
    assert(ep(msp5[7], Person("nicoletta", "mazzoleni", 52)));
    // ahead
    msp5.remove(Person("claudio", "rota", 26));
    assert(msp5.size() == 7);
    assert(ep(msp5[0], Person("simone", "mottadelli", 22)));
    msp5.remove(Person("simone", "mottadelli", 22));
    assert(msp5.size() == 6);
    assert(ep(msp5[0], Person("alessandro", "sorrentino", 21)));
    assert(ep(msp5[1], Person("matteo", "paolella", 23)));
    // in the middle
    msp5.remove(Person("andrea", "malerba", 21));
    assert(msp5.size() == 5);
    assert(ep(msp5[4], Person("nicoletta", "mazzoleni", 52)));
    msp5.remove(Person("matteo", "paolella", 23));
    assert(msp5.size() == 4);
    assert(ep(msp5[2], Person("burt", "ratti", 25)));
    // removal of  an element that doesn't exist
    try {
        msp5.remove(Person("claudio", "rota", 30));
        assert(false);
    }
    catch(const std::runtime_error& error) {}
    try {
        msp5.remove(Person("stefano", "micheli", 21));
        assert(false);
    }
    catch(const std::runtime_error& error) {}
    try {
        msp5.remove(Person("andreina", "milani", 23));
        assert(false);
    }
    catch(const std::runtime_error& error) {}
    std::cout << "testPerson : remove - OK" << std::endl;

    // OPERATOR<<
    std::cout << s << std::endl;
    std::cout << "testPerson : operator<< - OK" << std::endl;
    std::cout << "**********testPerson : END**********" << std::endl;
}

void testString() {
    std::cout << "**********testString : BEGIN**********" << std::endl;
    MySetString s = mySetString();
    equal_string es;

    // SIZE
    assert(s.size() == 10);
    std::cout << "testString : size - OK" << std::endl;

    // DEFAULT CONSTRUCTOR
    MySetString mss;
    assert(mss.size() == 0);
    std::cout << "testString : default construtor - OK" << std::endl;

    // COPY CONSTRUCTOR
    MySetString mss1(s);
    assert(mss1.size() == 10);
    assert(es(mss1[7], "cristina"));
    assert(es(mss1[0], "claudio"));
    assert(es(mss1[3], "alessandro"));
    assert(es(mss1[9], "gaia"));
    std::cout << "testString : copy construtor - OK" << std::endl;

    // OPERATOR=
    MySetString mss2 = mss1;
    assert(mss2.size() == 10);
    assert(es(mss2[3], "alessandro"));
    assert(es(mss2[0], "claudio"));
    assert(es(mss2[9], "gaia"));
    assert(es(mss2[5], "andrea"));
    std::cout << "testString : operator= - OK" << std::endl;

    // OPERATOR[]
    assert(es(mss2[0], "claudio"));
    assert(!es(mss2[3], "claudio"));
    assert(es(mss2[2], "stefano"));
    assert(es(mss2[6], "daniela"));
    assert(es(mss2[9], "gaia"));
    std::cout << "testString : operator[] - OK" << std::endl;

    // CONSTRUCTOR WITH ITERATOR
    MySetString::const_iterator b = s.begin(), e = s.end();
    MySetString mss3(b, e);
    assert(mss3.size() == 10);
    assert(es(mss3[1], "simone"));
    assert(es(mss3[9], "gaia"));
    assert(es(mss3[3], "alessandro"));
    assert(es(mss3[0], "claudio"));
    std::cout << "testString : constructor with iterators - OK" << std::endl;

    // ADD
    MySetString mss4(s);
    // addition of element that already exists
    // in the middle
    try {
        mss4.add("simone");
        assert(false);
    }
    catch(const std::runtime_error& error) {}
    // ahead
    try {
        mss4.add("claudio");
        assert(false);
    }
    catch(const std::runtime_error& error) {}
    // at the end
    try {
        mss4.add("gaia");
        assert(false);
    }
    catch(const std::runtime_error& error) {}
    // addition of new element that doesn't exist
    mss4.add("manuel");
    assert(mss4.size() == 11);
    assert(es(mss4[10], "manuel"));
    mss4.add("michele");
    mss4.add("francesco");
     assert(es(mss4[12], "francesco"));
    assert(mss4.size() == 13);
    mss4.add("marco");
    assert(mss4.size() == 14);
    mss4.add("giovanni");
     assert(es(mss4[14], "giovanni"));
    assert(mss4.size() == 15);
    std::cout << "testString : add - OK" << std::endl;

    // REMOVE
    MySetString mss5(s);
    // removal of an existing element
    // at the end
    mss5.remove("gaia");
    assert(mss5.size() == 9);
     assert(es(mss5[8], "burt"));
    mss5.remove("burt");
    assert(mss5.size() == 8);
    assert(es(mss5[7],"cristina"));
    // ahead
    mss5.remove("claudio");
    assert(mss5.size() == 7);
    assert(es(mss5[0],"simone"));
    mss5.remove("simone");
    assert(mss5.size() == 6);
    assert(es(mss5[0], "stefano"));
    assert(es(mss5[1], "alessandro"));
    // in the middle
    mss5.remove("matteo");
    assert(mss5.size() == 5);
    assert(es(mss5[4], "cristina"));
    mss5.remove("andrea");
    assert(mss5.size() == 4);
    assert(es(mss5[3], "cristina"));
    // removal of  an element that doesn't exist
    try {
        mss5.remove("massimo");
        assert(false);
    }
    catch(const std::runtime_error& error) {}
    try {
        mss5.remove("michele");
        assert(false);
    }
    catch(const std::runtime_error& error) {}
    try {
        mss5.remove("marco");
        assert(false);
    }
    catch(const std::runtime_error& error) {}
    std::cout << "testString : remove - OK" << std::endl;

    // OPERATOR<<
    std::cout << s << std::endl;
    std::cout << "testString : operator<< - OK" << std::endl;
    std::cout << "**********testString : END**********" << std::endl;
}

void testFilterOutInt() {
    std::cout << "**********testFilterOutInt : BEGIN**********" << std::endl;
    MySetInt s = mySetInt(0);
    MySetInt filtered = filter_out(s, is_odd());
    assert(filtered.size() == 5);
    assert(filtered[0] == 0);
    assert(filtered[1] != 1);
    assert(filtered[3] == 6);
    assert(filtered[4] == 8);
    std::cout << filtered << std::endl;
    std::cout << "**********testFilterOutInt : END**********" << std::endl;
}

void testFilterOutString() {
    std::cout << "**********testFilterOutString : BEGIN**********" << std::endl;
    MySetString s = mySetString();
    MySetString filtered = filter_out(s, even_length());
    equal_string e;
    assert(filtered.size() == 3);
    assert(e(filtered[0], "claudio"));
    assert(e(filtered[1], "stefano"));
    assert(e(filtered[2], "daniela"));
    std::cout << filtered << std::endl;
    std::cout << "**********testFilterOutString : BEGIN**********" << std::endl;
}

void testFilterOutPerson() {
    std::cout << "**********testFilterOutPerson : BEGIN**********" << std::endl;
    MySetPerson s = mySetPerson();
    MySetPerson filtered = filter_out(s, is_over_25());
    equal_person e;
    assert(filtered.size() == 8);
    assert(e(filtered[0], Person("simone", "mottadelli", 22)));
    assert(e(filtered[2], Person("matteo", "paolella", 23)));
    assert(e(filtered[7], Person("andrea", "milani", 23)));
    std::cout << filtered << std::endl;
    std::cout << "**********testFilterOutPerson : END**********" << std::endl;
}

void testConcatInt() {
    std::cout << "**********testConcatInt : BEGIN**********" << std::endl;
    MySetInt sx = mySetInt(0);
    MySetInt dx = mySetInt(10);
    MySetInt result = sx + dx;
    assert(result.size() == 20);
    assert(result[2] == 2);
    assert(result[13] == 13);
    std::cout << result << std::endl;
    std::cout << "**********testConcatInt : END**********" << std::endl;
}

void testConcatString() {
    std::cout << "**********testConcatString : BEGIN**********" << std::endl;
    equal_string e;
    MySetString sx = mySetString();
    MySetString dx;
    dx.add("francesco");
    dx.add("michele");
    dx.add("giovanni");
    MySetString result = sx + dx;
    assert(result.size() == 13);
    assert(e(result[0], "claudio"));
    assert(e(result[11], "michele"));
    std::cout << result << std::endl;
    std::cout << "**********testConcatInt : END**********" << std::endl;
}

void testConcatPerson() {
    std::cout << "**********testConcatPerson : BEGIN**********" << std::endl;
    equal_person e;
    MySetPerson sx = mySetPerson();
    MySetPerson dx;
    dx.add(Person("giulio", "scotti", 26));
    dx.add(Person("francesca", "martini", 24));
    dx.add(Person("gabriella", "rota", 45));
    dx.add(Person("plinia", "magni", 80));
    MySetPerson result = sx + dx;
    assert(result.size() == 14);
    assert(e(result[1], Person("simone", "mottadelli", 22)));
    assert(e(result[4], Person("stefano", "zuccarella", 21)));
    assert(e(result[11], Person("francesca", "martini", 24)));
    assert(e(result[13], Person("plinia", "magni", 80)));
    std::cout << result << std::endl;
    std::cout << "**********testConcatPerson : END**********" << std::endl;
}

int main() {
    std::cout << "**********BEGIN TESTS**********" << std::endl;
    // test with int type
    testInt();
    std::cout << std::endl;
    // test with string type
    testString();
    std::cout << std::endl;
    // test with custom (Person) type
    testPerson();
    std::cout << std::endl;

    // test filter_out with int type
    testFilterOutInt();
    std::cout << std::endl;
    // test filter_out with string type
    testFilterOutString();
    std::cout << std::endl;
    // test filter_out with custom (Person) type
    testFilterOutPerson();
    std::cout << std::endl;
    // test operator+ with int type
    testConcatInt();
    std::cout << std::endl;
    // test operator+ with string type
    testConcatString();
    std::cout << std::endl;
    // test operator+ with custom (Person) type
    testConcatPerson();

    std::cout << std:: endl << "**********END TESTS: ALL TEST PASSED**********" << std::endl;
    return 0;
}
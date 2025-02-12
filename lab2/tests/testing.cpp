#define CATCH_CONFIG_MAIN // Просит Catch2 реализовать свой main, снимая э>#include <catch2/catch.hpp>
#include "../table/table.h"
#include "../resource/resource.h"

using namespace Prog2;

TEST_CASE("resource constructor") {
    SECTION("default") {
        Resource r;
        REQUIRE(r.GetName() == std::string("AAA"));
        REQUIRE(r.GetConsumption() == 1);
        REQUIRE(r.GetProduction() == 1);
        REQUIRE(r.GetPrice() == 1);
    }
    SECTION("construct by name and price") {
        Resource r("rrr", 33);
        REQUIRE(r.GetName() == std::string("rrr"));
        REQUIRE(r.GetConsumption() == 1);
        REQUIRE(r.GetProduction() == 1);
        REQUIRE(r.GetPrice() == 33);
    }
    SECTION("construct by name, consumption, production and price") {
        Resource r("ttt", 5, 5, 5);
        REQUIRE(r.GetName() == std::string("ttt"));
        REQUIRE(r.GetConsumption() == 5);
        REQUIRE(r.GetProduction() == 5);
        REQUIRE(r.GetPrice() == 5);
    }
}

TEST_CASE("resource methods") {
    SECTION("profit") {
        Resource r("ttt", 5, 6, 5);
        REQUIRE(r.profit() == 35);
        Resource u("ttt", 5, 5, 5);
        REQUIRE(u.profit() == 0);
        Resource p("ttt", 6, 5, 5);
        REQUIRE(p.profit() == -35);
    }
    SECTION("increase") {
        Resource r("ttt", 5, 6, 5);
        r.increase(1);
        REQUIRE(r.profit() == 35);
        r.increase(2);
        REQUIRE(r.profit() == 70);
        REQUIRE_THROWS(r.increase(-10));
    }
    SECTION("Setters") {
        Resource r;
        r.setName("uuu");
        r.setConsumption(4);
        r.setProduction(3);
        r.setPrice(2);
        REQUIRE(r.GetName() == std::string("uuu"));
        REQUIRE(r.GetConsumption() == 4);
        REQUIRE(r.GetProduction() == 3);
        REQUIRE(r.GetPrice() == 2);
    }
}


TEST_CASE("resource operators") {
    SECTION("(+)") {
        Resource r("ttt", 5, 6, 5);
        Resource t("ttt", 7, 8, 9);
        Resource y = r + t;
        REQUIRE(y.GetName() == std::string("ttt"));
        REQUIRE(y.GetConsumption() == 12);
        REQUIRE(y.GetProduction() == 14);
        REQUIRE(y.GetPrice() == 5);
    }
    SECTION("(==)") {
        Resource r("ttt", 5, 6, 5);
        Resource t("ttt", 5, 6, 5);
        Resource y("uuu", 5, 5, 5);
        REQUIRE(r == t);
        REQUIRE(!(y == t));
    }
    SECTION("(<)") {
        Resource r("aaa", 5, 6, 5);
        Resource t("fff", 5, 6, 5);
        Resource y("bbb", 5, 5, 5);
        REQUIRE(r < t);
        REQUIRE(!(t < y));
    }
    SECTION("(=)") {
        Resource r("ttt", 5, 6, 5);
        Resource y = r;
        REQUIRE(y.GetName() == std::string("ttt"));
        REQUIRE(y.GetConsumption() == 5);
        REQUIRE(y.GetProduction() == 6);
        REQUIRE(y.GetPrice() == 5);
    }
    SECTION("(<<)") {
        std::stringstream out;
        Resource r("ttt", 5, 6, 5);
        out << r;
        std::string str;
        getline(out, str);
        REQUIRE(str == "ttt 5 6 5");
    }
    SECTION("(>>)") {
        std::stringstream in1("rrr 116 116 116\n");
        Resource r;
        in1 >> r;
        REQUIRE(r.GetName() == std::string("rrr"));
        REQUIRE(r.GetConsumption() == 116);
        REQUIRE(r.GetProduction() == 116);
        REQUIRE(r.GetPrice() == 116);

        std::stringstream in2("rrr t t t\n");
        in2 >> r;
        REQUIRE(r.GetName() == std::string("rrr"));
        REQUIRE(r.GetConsumption() == 116);
        REQUIRE(r.GetProduction() == 116);
        REQUIRE(r.GetPrice() == 116);

        std::stringstream in3("rrr 0 -1 -5\n");
        in3 >> r;
        REQUIRE(r.GetName() == std::string("rrr"));
        REQUIRE(r.GetConsumption() == 116);
        REQUIRE(r.GetProduction() == 116);
        REQUIRE(r.GetPrice() == 116);
    }
}





TEST_CASE("table constructors") {
    SECTION("construct a default") {
        Table t;
        REQUIRE(t.Get_m_size() == 0);
        REQUIRE(t.Get_c_size() == 0);
        REQUIRE(t.Get_ks() == nullptr);
    }
    SECTION("copying constructor") {
        Table t;
        Resource r("first", 4, 4, 4);
        t += r;
        Table k(t);
        REQUIRE(k.Get_m_size() == t.Get_m_size());
        REQUIRE(k.Get_c_size() == t.Get_c_size());
        REQUIRE(t.Get_ks()[0] == k.Get_ks()[0]);
    }
    SECTION("moving constructor") {
        Table t;
        Resource r("second", 4, 4, 4);
        t += r;
        Table k(std::move(t));
        Resource p = k[std::string("second")];
        REQUIRE(p.GetName() == std::string("second"));
        REQUIRE(p.GetConsumption() == 4);
        REQUIRE(p.GetProduction() == 4);
        REQUIRE(p.GetPrice() == 4);
        REQUIRE(t.Get_ks() == nullptr);
    }
}




TEST_CASE("table operators") {
    SECTION("copying (=)") {
        Table t;
        Resource r("lll", 4, 4, 4);
        t += r;
        Table k = t;
        t = t;
        REQUIRE(k.Get_m_size() == t.Get_m_size());
        REQUIRE(k.Get_c_size() == t.Get_c_size());
        REQUIRE(t.Get_ks()[0] == k.Get_ks()[0]);
    }
    SECTION("moving (=)") {
        Table t;
        Resource r("kkk", 4, 4, 4);
        t += r;
        Table k;
        k = std::move(t);
        Resource p = k[std::string("kkk")];
        REQUIRE(p.GetName() == std::string("kkk"));
        REQUIRE(p.GetConsumption() == 4);
        REQUIRE(p.GetProduction() == 4);
        REQUIRE(p.GetPrice() == 4);
        REQUIRE(t.Get_ks() == nullptr);
    }
    SECTION("(+=)") {
        Table t;
        Resource r("123", 4, 4, 4);
        t += r;
        Resource p = t[std::string("123")];
        REQUIRE(p.GetName() == std::string("123"));
        REQUIRE(p.GetConsumption() == 4);
        REQUIRE(p.GetProduction() == 4);
        REQUIRE(p.GetPrice() == 4);
    }
    SECTION("([])") {
        Table t;
        Resource r("ooo", 99, 7, 6);
        t += r;
        Resource p = t[std::string("ooo")];
        REQUIRE(p.GetName() == std::string("ooo"));
        REQUIRE(p.GetConsumption() == 99);
        REQUIRE(p.GetProduction() == 7);
        REQUIRE(p.GetPrice() == 6);
        REQUIRE_THROWS(t[std::string("___")]);
    }
    SECTION("([]) const") {
        Table k;
        Resource r("rt", 4, 4, 4);
        k += r;
        const Table t = k;
        const std::string std = "rt";
        const Resource& p = t[std];
        REQUIRE(p.GetName() == std::string("rt"));
        REQUIRE(p.GetConsumption() == 4);
        REQUIRE(p.GetProduction() == 4);
        REQUIRE(p.GetPrice() == 4);
        REQUIRE_THROWS(t[std::string(".....")]);
    }
    SECTION("(<<)") {
        Table t;
        std::stringstream out;
        Resource r("aaa", 5, 6, 5);
        t += r;
        out << t;
        std::string str;
        getline(out, str);
        REQUIRE(str == "1. aaa 5 6 5");

        Table k;
        std::stringstream out2;
        out2 << k;
        std::string str2;
        getline(out2, str2);
        REQUIRE(str2 == "The table is empty");
    }
    SECTION("(>>)") {
        std::stringstream in1("2 aaa 116 116 116 bbb 2 2 2\n");
        Table t;
        in1 >> t;
        REQUIRE(t.Get_ks()[0].GetName() == std::string("aaa"));
        REQUIRE(t.Get_ks()[0].GetConsumption() == 116);
        REQUIRE(t.Get_ks()[0].GetProduction() == 116);
        REQUIRE(t.Get_ks()[0].GetPrice() == 116);

        REQUIRE(t.Get_ks()[1].GetName() == std::string("bbb"));
        REQUIRE(t.Get_ks()[1].GetConsumption() == 2);
        REQUIRE(t.Get_ks()[1].GetProduction() == 2);
        REQUIRE(t.Get_ks()[1].GetPrice() == 2);

        std::stringstream in2("1 rrr t t t\n");
        in2 >> t;
        REQUIRE(t.Get_ks()[0].GetName() == std::string("aaa"));
        REQUIRE(t.Get_ks()[0].GetConsumption() == 116);
        REQUIRE(t.Get_ks()[0].GetProduction() == 116);
        REQUIRE(t.Get_ks()[0].GetPrice() == 116);

        std::stringstream in3("1 rrr 0 -1 -5\n");
        in3 >> t;
        REQUIRE(t.Get_ks()[1].GetName() == std::string("bbb"));
        REQUIRE(t.Get_ks()[1].GetConsumption() == 2);
        REQUIRE(t.Get_ks()[1].GetProduction() == 2);
        REQUIRE(t.Get_ks()[1].GetPrice() == 2);
    }}

    TEST_CASE("table methods") {
        SECTION("removal") {
            Table t;
            Resource r("name", 4, 4, 4);
            Resource y("lllll", 4, 4, 4);
            t += r;
            t += y;
            t.removal(std::string("name"));
            REQUIRE_THROWS(t[std::string("name")]);
            Resource p = t[std::string("lllll")];
            REQUIRE(p.GetName() == std::string("lllll"));
        }
        SECTION("binary_search") {
            Table t;
            Resource r("name", 4, 4, 4);
            Resource y("lllll", 4, 4, 4);
            Resource i("101", 8, 8, 8);
            t += r;
            t += y;
            t += i;
            Resource p = t[std::string("name")];
            REQUIRE(p.GetName() == std::string("name"));
            REQUIRE(p.GetConsumption() == 4);
            REQUIRE(p.GetProduction() == 4);
            REQUIRE(p.GetPrice() == 4);
            p = t[std::string("101")];
            REQUIRE(p.GetName() == std::string("101"));
            REQUIRE(p.GetConsumption() == 8);
            REQUIRE(p.GetProduction() == 8);
            REQUIRE(p.GetPrice() == 8);
            REQUIRE_THROWS(t[std::string("laba")]);
        }
        SECTION("resize") {
            Table t;
            for (int i = 0; i < 10; i++) {
                t += Resource("i", i, i, i);
            }
            std::string str = "elem";
            t += Resource(str, 44, 44, 44);
            REQUIRE(t.Get_c_size() == 11);
            REQUIRE(t.Get_m_size() == 20);
            t.removal(std::string("elem"));
            REQUIRE(t.Get_c_size() == 10);
            REQUIRE(t.Get_m_size() == 10);
        }
        SECTION("condition") {
            Table t;
            REQUIRE(t.condition() == std::string("empty"));
            for (int i = 0; i < 9; i++) {
                t += Resource("i", i, i, i);
            }
            REQUIRE(t.condition() == std::string("partially filled"));
            std::string str = "elem";
            t += Resource(str, 44, 44, 44);
            REQUIRE(t.condition() == std::string("full"));
        }
        SECTION("init_vector") {
            Table t;
            Resource vector[] = {
                    Resource("aa", 11, 1, 1),
                    Resource("ff", 22, 2, 2),
                    Resource("bb", 33, 3, 3),
                    Resource("gg", 44, 4, 4),
                    Resource("cc", 55, 5, 5),
                    Resource("ll", 66, 6, 6),
            };
            t.init_vector(vector, 3);
            REQUIRE(t.Get_c_size() == 3);
            REQUIRE_THROWS(t.init_vector(vector, -3));
        }
        SECTION("rename") {
            Table t;
            Resource vector[] = {
                    Resource("aa", 11, 1, 1),
                    Resource("ff", 22, 2, 2),
                    Resource("bb", 33, 3, 3),
                    Resource("gg", 44, 4, 4),
                    Resource("cc", 55, 5, 5),
                    Resource("ll", 66, 6, 6),
            };
            t.init_vector(vector, 3);
            Resource a = t[std::string("aa")];
            t.rename(std::string("aa"), std::string("oo"));
            Resource o = t[std::string("oo")];
            REQUIRE(o.GetName() == std::string("oo"));
            REQUIRE(a.GetConsumption() == o.GetConsumption());
            REQUIRE(a.GetProduction() == o.GetProduction());
            REQUIRE(a.GetPrice() == o.GetPrice());
        }
        SECTION("increase") {
            Table t;
            t += Resource("1", 1, 2, 10);
            t += Resource("2", 2, 3, 10);
            REQUIRE(t.profit() == 140);
            t.increase(10);
            REQUIRE(t.profit() == 1400);
        }
        SECTION("profit") {
            Table t;
            t += Resource("1", 1, 2, 10);
            t += Resource("2", 2, 3, 10);
            REQUIRE(t.profit() == 140);
            t += Resource("2", 2, 3, 10);
            REQUIRE(t.profit() == 210);
        }
    }
}    

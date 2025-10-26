#include <gtest/gtest.h>
#include <sstream>

#include "Figure.hpp"
#include "Hexagon.hpp"
#include "Octagon.hpp"
#include "Pentagon.hpp"


TEST(PointTest, OutputOperator) {
    Point p = {1.0, 2.0};
    std::stringstream ss;
    ss << p;
    ASSERT_EQ(ss.str(), "(1, 2)");
}

class MockFigure : public Figure {
public:
    Point geomCenter() const override { return {0.0, 0.0}; }
    void print(std::ostream &os) const override { os << "MockFigure"; }
    void read(std::istream &is) override {}
    operator double() const override { return 0.0; }
    Figure *clone() const override { return new MockFigure(*this); }
    ~MockFigure() override {}
};

TEST(ArrayFTest, DefaultConstructor) {
    ArrayF arr;
    ASSERT_EQ(arr.GetSize(), 0);
}

TEST(ArrayFTest, PushItem) {
    ArrayF arr;
    MockFigure *mf1 = new MockFigure();
    arr.PushItem(mf1);
    ASSERT_EQ(arr.GetSize(), 1);
    ASSERT_EQ(arr.GetItem(0), mf1);

    MockFigure *mf2 = new MockFigure();
    arr.PushItem(mf2);
    ASSERT_EQ(arr.GetSize(), 2);
    ASSERT_EQ(arr.GetItem(1), mf2);
}

TEST(ArrayFTest, GetSize) {
    ArrayF arr;
    ASSERT_EQ(arr.GetSize(), 0);
    arr.PushItem(new MockFigure());
    ASSERT_EQ(arr.GetSize(), 1);
}

TEST(ArrayFTest, GetItem) {
    MockFigure *mf = new MockFigure();
    ArrayF arr;
    arr.PushItem(mf);
    ASSERT_EQ(arr.GetItem(0), mf);
    ASSERT_THROW(arr.GetItem(99), std::out_of_range);
}

TEST(ArrayFTest, DeleteItem) {
    MockFigure *mf1 = new MockFigure();
    MockFigure *mf2 = new MockFigure();
    ArrayF arr;
    arr.PushItem(mf1);
    arr.PushItem(mf2);

    arr.DeleteItem(0);
    ASSERT_EQ(arr.GetSize(), 1);
    ASSERT_EQ(arr.GetItem(0), mf2);
    ASSERT_THROW(arr.DeleteItem(99), std::out_of_range);
}

TEST(ArrayFTest, ConstructorWithSize) {
    ArrayF arr(5, new MockFigure());
    ASSERT_EQ(arr.GetSize(), 5);
    for (size_t i = 0; i < arr.GetSize(); ++i) {
        ASSERT_NE(arr.GetItem(i), nullptr);
    }
}

TEST(ArrayFTest, CopyConstructor) {
    ArrayF arr1;
    MockFigure *mf1 = new MockFigure();
    arr1.PushItem(mf1);
    ArrayF arr2 = arr1;
    ASSERT_EQ(arr2.GetSize(), 1);
    ASSERT_NE(arr2.GetItem(0), mf1);
    ASSERT_NE(arr2.GetItem(0), nullptr);
}

TEST(ArrayFTest, CopyAssignment) {
    ArrayF arr1;
    MockFigure *mf1 = new MockFigure();
    arr1.PushItem(mf1);
    ArrayF arr2;
    arr2 = arr1;
    ASSERT_EQ(arr2.GetSize(), 1);
    ASSERT_NE(arr2.GetItem(0), mf1);
    ASSERT_NE(arr2.GetItem(0), nullptr);
}

TEST(ArrayFTest, Resize) {
    ArrayF arr;
    arr.PushItem(new MockFigure());
    arr.PushItem(new MockFigure());
    arr.Resize(1);
    ASSERT_EQ(arr.GetSize(), 1);
    ASSERT_THROW(arr.GetItem(1), std::out_of_range);
    arr.Resize(3);
    ASSERT_EQ(arr.GetSize(), 3);
    ASSERT_NE(arr.GetItem(0), nullptr);
    ASSERT_EQ(arr.GetItem(1), nullptr);
    ASSERT_EQ(arr.GetItem(2), nullptr);
}

TEST(ArrayFTest, PopItem) {
    ArrayF arr;
    MockFigure *mf1 = new MockFigure();
    arr.PushItem(mf1);
    arr.PopItem();
    ASSERT_EQ(arr.GetSize(), 0);
    ASSERT_THROW(arr.PopItem(), std::out_of_range);
}

TEST(ArrayFTest, Back) {
    ArrayF arr;
    MockFigure *mf1 = new MockFigure();
    arr.PushItem(mf1);
    ASSERT_EQ(arr.Back(), mf1);
    arr.PopItem();
    ASSERT_THROW(arr.Back(), std::out_of_range);
}

TEST(PentagonTest, DefaultConstructor) {
    Pentagon p;
    std::stringstream ss;
    p.print(ss);
    ASSERT_NE(ss.str().find("Vertex 1: 0 0"), std::string::npos);
}

TEST(PentagonTest, Read) {
    Pentagon p;
    std::istringstream iss("10 10\n20 20\n30 30\n40 40\n50 50\n");
    p.read(iss);
    std::stringstream ss;
    p.print(ss);
    ASSERT_NE(ss.str().find("Vertex 1: 10 10"), std::string::npos);
    ASSERT_NE(ss.str().find("Vertex 5: 50 50"), std::string::npos);
}

TEST(PentagonTest, Print) {
    Pentagon p;
    std::istringstream iss("1 1\n2 2\n3 3\n4 4\n5 5\n");
    p.read(iss);
    std::stringstream ss;
    p.print(ss);
    ASSERT_EQ(ss.str(), "Vertex 1: 1 1\nVertex 2: 2 2\nVertex 3: 3 3\nVertex 4: 4 4\nVertex 5: 5 5\n");
}

TEST(PentagonTest, GeomCenter) {
    Pentagon p;
    std::istringstream iss("0 0\n10 0\n10 10\n5 15\n0 10\n");
    p.read(iss);
    Point center = p.geomCenter();
    ASSERT_NEAR(center.x, 5.0, 0.001);
    ASSERT_NEAR(center.y, 6.333333333333333, 0.001);
}

TEST(PentagonTest, Area) {
    Pentagon p;
    std::istringstream iss("0 0\n10 0\n10 10\n5 15\n0 10\n");
    p.read(iss);
    double area = static_cast<double>(p);
    ASSERT_NEAR(area, 125.00, 0.001);
}

TEST(PentagonTest, Clone) {
    Pentagon p1;
    std::istringstream iss("1 1\n2 2\n3 3\n4 4\n5 5\n");
    p1.read(iss);

    Figure *p2 = p1.clone();
    std::stringstream ss1, ss2;
    p1.print(ss1);
    p2->print(ss2);
    ASSERT_EQ(ss1.str(), ss2.str());
    delete p2;
}

TEST(HexagonTest, DefaultConstructor) {
    Hexagon h;
    std::stringstream ss;
    h.print(ss);
    ASSERT_NE(ss.str().find("Vertex 1: 0 0"), std::string::npos);
}

TEST(HexagonTest, Read) {
    Hexagon h;
    std::istringstream iss("10 10\n20 20\n30 30\n40 40\n50 50\n60 60\n");
    h.read(iss);
    std::stringstream ss;
    h.print(ss);
    ASSERT_NE(ss.str().find("Vertex 1: 10 10"), std::string::npos);
    ASSERT_NE(ss.str().find("Vertex 6: 60 60"), std::string::npos);
}

TEST(HexagonTest, Print) {
    Hexagon h;
    std::istringstream iss("1 1\n2 2\n3 3\n4 4\n5 5\n6 6\n");
    h.read(iss);
    std::stringstream ss;
    h.print(ss);
    ASSERT_EQ(ss.str(), "Vertex 1: 1 1\nVertex 2: 2 2\nVertex 3: 3 3\nVertex 4: 4 4\nVertex 5: 5 5\nVertex 6: 6 6\n");
}

TEST(HexagonTest, GeomCenter) {
    Hexagon h;
    std::istringstream iss("0 0\n10 0\n15 8.66\n10 17.32\n0 17.32\n-5 8.66\n");
    h.read(iss);
    Point center = h.geomCenter();
    ASSERT_NEAR(center.x, 5.0, 0.001);
    ASSERT_NEAR(center.y, 8.66, 0.001);
}

TEST(HexagonTest, Area) {
    Hexagon h;
    std::istringstream iss("0 0\n10 0\n15 8.66\n10 17.32\n0 17.32\n-5 8.66\n");
    h.read(iss);
    double area = static_cast<double>(h);
    ASSERT_NEAR(area, 259.800, 0.001);
}

TEST(HexagonTest, Clone) {
    Hexagon h1;
    std::istringstream iss("1 1\n2 2\n3 3\n4 4\n5 5\n6 6\n");
    h1.read(iss);

    Figure *h2 = h1.clone();
    std::stringstream ss1, ss2;
    h1.print(ss1);
    h2->print(ss2);
    ASSERT_EQ(ss1.str(), ss2.str());
    delete h2;
}

TEST(OctagonTest, DefaultConstructor) {
    Octagon o;
    std::stringstream ss;
    o.print(ss);
    ASSERT_NE(ss.str().find("Vertex 1: 0 0"), std::string::npos);
}

TEST(OctagonTest, Read) {
    Octagon o;
    std::istringstream iss("10 10\n20 20\n30 30\n40 40\n50 50\n60 60\n70 70\n80 80\n");
    o.read(iss);
    std::stringstream ss;
    o.print(ss);
    ASSERT_NE(ss.str().find("Vertex 1: 10 10"), std::string::npos);
    ASSERT_NE(ss.str().find("Vertex 8: 80 80"), std::string::npos);
}

TEST(OctagonTest, Print) {
    Octagon o;
    std::istringstream iss("1 1\n2 2\n3 3\n4 4\n5 5\n6 6\n7 7\n8 8\n");
    o.read(iss);
    std::stringstream ss;
    o.print(ss);
    ASSERT_EQ(ss.str(), "Vertex 1: 1 1\nVertex 2: 2 2\nVertex 3: 3 3\nVertex 4: 4 4\nVertex 5: 5 5\nVertex 6: 6 6\nVertex "
                        "7: 7 7\nVertex 8: 8 8\n");
}

TEST(OctagonTest, GeomCenter) {
    Octagon o;
    std::istringstream iss("0 0\n10 0\n14.14 4.14\n14.14 14.14\n10 18.28\n0 18.28\n-4.14 14.14\n-4.14 4.14\n");
    o.read(iss);
    Point center = o.geomCenter();
    ASSERT_NEAR(center.x, 5.0, 0.001);
    ASSERT_NEAR(center.y, 9.14, 0.001);
}

TEST(OctagonTest, Area) {
    Octagon o;
    std::istringstream iss("0 0\n10 0\n14.14 4.14\n14.14 14.14\n10 18.28\n0 18.28\n-4.14 14.14\n-4.14 4.14\n");
    o.read(iss);
    double area = static_cast<double>(o);
    ASSERT_NEAR(area, 299.879, 0.001);
}

TEST(OctagonTest, Clone) {
    Octagon o1;
    std::istringstream iss("1 1\n2 2\n3 3\n4 4\n5 5\n6 6\n7 7\n8 8\n");
    o1.read(iss);

    Figure *o2 = o1.clone();
    std::stringstream ss1, ss2;
    o1.print(ss1);
    o2->print(ss2);
    ASSERT_EQ(ss1.str(), ss2.str());
    delete o2;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
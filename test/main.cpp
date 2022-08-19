#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

extern "C" {
#include <vector.h>
}

TEST(VectorPtrTest, TestContiguous) {
  struct vector *v = NULL;
  vector_create(&v);
  for (double i = 0.0; i < 10000; ++i) {
    vector_push_ptr_back(v, &i, sizeof(double));
  }
  for (double i = 0.0; i < 10000; ++i) {
    double returned_from_vector =
        *(static_cast<double *>(vector_get_ptr_at(v, static_cast<size_t>(i))));
    EXPECT_EQ(returned_from_vector, i);
  }
  vector_destroy(&v);
}

TEST(VectorPtrTest, TestMixed) {
  struct vector *v = NULL;
  vector_create(&v);

  double double_value = 14565.0;
  vector_push_ptr_back(v, &double_value, sizeof(double));

  char char_value = 5;
  vector_push_ptr_back(v, &char_value, sizeof(char));

  struct structure {
    int first_field;
    double second_field;
    size_t third_field;
  } struct_value;
  struct_value.first_field = -1;
  struct_value.second_field = 2.0;
  struct_value.third_field = 3;
  vector_push_ptr_back(v, &struct_value, sizeof(structure));

  char string_value[13] = "test string\0";
  vector_push_ptr_back(v, &string_value,
                       sizeof(char) * (strlen(string_value) + 1));

  std::string class_value = "test class std::string";
  vector_push_ptr_back(v, &class_value, sizeof(std::string));

  double double_value_returned =
      *(static_cast<double *>(vector_get_ptr_at(v, 0)));
  EXPECT_EQ(double_value_returned, double_value);

  char char_value_returned = *(static_cast<char *>(vector_get_ptr_at(v, 1)));
  EXPECT_EQ(char_value_returned, char_value);

  structure struct_value_returned =
      *(static_cast<structure *>(vector_get_ptr_at(v, 2)));
  EXPECT_EQ(struct_value_returned.first_field, struct_value.first_field);
  EXPECT_EQ(struct_value_returned.second_field, struct_value.second_field);
  EXPECT_EQ(struct_value_returned.third_field, struct_value.third_field);

  char *string_value_returned = static_cast<char *>(vector_get_ptr_at(v, 3));
  EXPECT_STREQ(string_value_returned, string_value);

  std::string class_value_returned =
      *(static_cast<std::string *>(vector_get_ptr_at(v, 4)));
  EXPECT_EQ(class_value_returned, class_value);

  vector_destroy(&v);
}

TEST(VectorPtrTest, TestSetAt) {
  struct vector *v = NULL;
  vector_create(&v);

  int a = -1;
  vector_push_ptr_back(v, &a, sizeof(int));

  double b = 2.0;
  vector_push_ptr_back(v, &b, sizeof(double));

  char c = 3;
  vector_push_ptr_back(v, &c, sizeof(char));

  std::string d = "hello";
  vector_push_ptr_back(v, &d, sizeof(std::string));

  vector_set_ptr_at(v, 0, &b, sizeof(double));
  vector_set_ptr_at(v, 1, &c, sizeof(char));
  vector_set_ptr_at(v, 2, &d, sizeof(std::string));
  vector_set_ptr_at(v, 3, &a, sizeof(int));

  double b_returned = *(static_cast<double *>(vector_get_ptr_at(v, 0)));
  EXPECT_EQ(b_returned, b);

  char c_returned = *(static_cast<char *>(vector_get_ptr_at(v, 1)));
  EXPECT_EQ(c_returned, c);

  std::string d_returned =
      *(static_cast<std::string *>(vector_get_ptr_at(v, 2)));
  EXPECT_EQ(d_returned, d);

  int a_returned = *(static_cast<int *>(vector_get_ptr_at(v, 3)));
  EXPECT_EQ(a_returned, a);

  vector_destroy(&v);
}

TEST(VectorValueTest, TestContiguous) {
  struct vector *v = NULL;
  vector_create(&v);
  for (double i = 0.0; i < 10000; ++i) {
    vector_push_back(v, i, double);
  }
  for (size_t i = 0; i < 10000; ++i) {
    double returned_from_vector = vector_get_at(v, i, double);
    EXPECT_EQ(returned_from_vector, i);
  }
  vector_destroy(&v);
}

TEST(VectorValueTest, TestMixed) {
  struct vector *v = NULL;
  vector_create(&v);

  double double_value = 14565.0;
  vector_push_back(v, double_value, double);

  char char_value = 5;
  vector_push_back(v, char_value, char);

  struct structure {
    int first_field;
    double second_field;
    size_t third_field;
  } struct_value;
  struct_value.first_field = -1;
  struct_value.second_field = 2.0;
  struct_value.third_field = 3;
  vector_push_back(v, struct_value, structure);

  char string_value[13] = "test string\0";
  vector_push_ptr_back(v, &string_value,
                       sizeof(char) * (strlen(string_value) + 1));

  std::string class_value = "test class std::string";
  vector_push_back(v, class_value, std::string);

  double double_value_returned = vector_get_at(v, 0, double);
  EXPECT_EQ(double_value_returned, double_value);

  char char_value_returned = vector_get_at(v, 1, char);
  EXPECT_EQ(char_value_returned, char_value);

  structure struct_value_returned = vector_get_at(v, 2, structure);
  EXPECT_EQ(struct_value_returned.first_field, struct_value.first_field);
  EXPECT_EQ(struct_value_returned.second_field, struct_value.second_field);
  EXPECT_EQ(struct_value_returned.third_field, struct_value.third_field);

  char *string_value_returned = static_cast<char *>(vector_get_ptr_at(v, 3));
  EXPECT_STREQ(string_value_returned, string_value);

  std::string class_value_returned = vector_get_at(v, 4, std::string);
  EXPECT_EQ(class_value_returned, class_value);

  vector_destroy(&v);
}

TEST(VectorValueTest, TestSetAt) {
  struct vector *v = NULL;
  vector_create(&v);

  int a = -1;
  vector_push_back(v, a, int);

  double b = 2.0;
  vector_push_back(v, b, double);

  char c = 3;
  vector_push_back(v, c, char);

  std::string d = "hello";
  vector_push_back(v, d, std::string);

  vector_set_at(v, 0, b, double);
  vector_set_at(v, 1, c, char);
  vector_set_at(v, 2, d, std::string);
  vector_set_at(v, 3, a, int);

  double b_returned = vector_get_at(v, 0, double);
  EXPECT_EQ(b_returned, b);

  char c_returned = vector_get_at(v, 1, char);
  EXPECT_EQ(c_returned, c);

  std::string d_returned = vector_get_at(v, 2, std::string);
  EXPECT_EQ(d_returned, d);

  int a_returned = vector_get_at(v, 3, int);
  EXPECT_EQ(a_returned, a);

  vector_destroy(&v);
}

/*
 * Will not work. Vector can add only lvalues. Know how to fix it? PM me at
Telegram @Adefe
 *
TEST(VectorValueTest, TestRValue) {
struct vector *v = NULL;
  vector_create(&v);

  vector_push_back(v, 123, int);
  vector_push_back(v, 321.0, double);
  vector_push_back(v, 222, char);

  EXPECT_EQ(vector_get_at(v, 0, int), 123);
  EXPECT_EQ(vector_get_at(v, 1, double), 321.0);
  EXPECT_EQ(vector_get_at(v, 2, char), 222);

  vector_destroy(&v);
}
*/

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

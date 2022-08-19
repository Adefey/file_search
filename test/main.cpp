#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

extern "C" {
#include <vector.h>
}

TEST(VectorTest, TestContiguous) {
  struct vector *v = NULL;
  create(&v);
  for (double i = 0.0; i < 10000; ++i) {
    push_back(v, &i, sizeof(double));
  }
  for (double i = 0.0; i < 10000; ++i) {
    double returned_from_vector =
        *(static_cast<double *>(get_at(v, static_cast<size_t>(i))));
    EXPECT_EQ(returned_from_vector, i);
  }
  destroy(&v);
}

TEST(VectorTest, TestMixed) {
  struct vector *v = NULL;
  create(&v);

  double double_value = 14565.0;
  push_back(v, &double_value, sizeof(double));

  char char_value = 5;
  push_back(v, &char_value, sizeof(char));

  struct structure {
    int first_field;
    double second_field;
    size_t third_field;
  } struct_value;
  struct_value.first_field = -1;
  struct_value.second_field = 2.0;
  struct_value.third_field = 3;
  push_back(v, &struct_value, sizeof(structure));

  char string_value[13] = "test string\0";
  push_back(v, &string_value, sizeof(char) * (strlen(string_value) + 1));

  std::string class_value = "test class std::string";
  push_back(v, &class_value, sizeof(std::string));

  double double_value_returned = *(static_cast<double *>(get_at(v, 0)));
  EXPECT_EQ(double_value_returned, double_value);

  char char_value_returned = *(static_cast<char *>(get_at(v, 1)));
  EXPECT_EQ(char_value_returned, char_value);

  structure struct_value_returned = *(static_cast<structure *>(get_at(v, 2)));
  EXPECT_EQ(struct_value_returned.first_field, struct_value.first_field);
  EXPECT_EQ(struct_value_returned.second_field, struct_value.second_field);
  EXPECT_EQ(struct_value_returned.third_field, struct_value.third_field);

  char *string_value_returned = static_cast<char *>(get_at(v, 3));
  EXPECT_STREQ(string_value_returned, string_value);

  std::string class_value_returned =
      *(static_cast<std::string *>(get_at(v, 4)));
  EXPECT_EQ(class_value_returned, class_value);

  destroy(&v);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

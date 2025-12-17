#include <gtest/gtest.h>
#include "Squirrel.h"
#include "Druid.h"
#include "Werewolf.h"

TEST(SquirrelTest, InteractionWithWerewolf) {
    Squirrel squirrel("Squirrel", 0, 0);
    Werewolf werewolf("Werewolf", 10, 10);

    testing::internal::CaptureStdout();
    squirrel.interact(&werewolf);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Squirrel kills Werewolf!\n");
}

TEST(SquirrelTest, InteractionWithDruid) {
    Squirrel squirrel("Squirrel", 0, 0);
    Druid druid("Druid", 20, 20);

    testing::internal::CaptureStdout();
    squirrel.interact(&druid);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Squirrel kills Druid!\n");
}

TEST(WerewolfTest, InteractionWithDruid) {
    Werewolf werewolf("Werewolf", 10, 10);
    Druid druid("Druid", 20, 20);

    testing::internal::CaptureStdout();
    werewolf.interact(&druid);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Werewolf kills Druid!\n");
}

TEST(DruidTest, InteractionWithAnyNPC) {
    Druid druid("Druid", 20, 20);
    Squirrel squirrel("Squirrel", 0, 0);
    Werewolf werewolf("Werewolf", 10, 10);

    testing::internal::CaptureStdout();
    druid.interact(&squirrel);
    druid.interact(&werewolf);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");
}

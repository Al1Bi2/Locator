#include "locator.hpp"
#include "gtest/gtest.h"

            TEST(Locator, zeroIfNotExists){
                Locator locator;
                auto subscriber= locator.getSubscriber("unknown");
                ASSERT_TRUE(subscriber.empty());
                
            }
            TEST(Locator, readJSON){
                Locator locator;
                locator.loadJSON("settings.json");
                locator.setSubscriberLocation("+79211111111", 10, 20);
                locator.setSubscriberLocation("+79212222222", 1, 2);
                auto subscribers = locator.getSubsciberInZone(123);
                ASSERT_EQ(subscribers.size(), 1);
                ASSERT_EQ(subscribers.front().get_id(), "+79212222222");
            }

            

            TEST(GetSubscriber, ReturnSubsciberDataIfSuscriberInDb)
            {
                Locator locator;

                locator.setSubscriberLocation("+79115555555", 10, 20);
                auto subscriber = locator.getSubscriber("+79115555555");
                ASSERT_FALSE(subscriber.empty());
                ASSERT_EQ(subscriber.get_x(), 10);
                ASSERT_EQ(subscriber.get_y(), 20);
            }

            TEST(GetSubscriber, ReturnSubscriberInZone)
            {
                Locator locator;
                locator.addCell(1000, "spb", 0, 0, 20);
                locator.setSubscriberLocation("+79115555555", 1, 2);
                auto subscribers = locator.getSubsciberInZone(1000);
                ASSERT_EQ(subscribers.size(), 1);
                ASSERT_EQ(subscribers.front().get_id(), "+79115555555");
            }

            TEST(Triggers, crossborder){
                Locator locator;
                locator.loadJSON("settings.json");
                 AbstractTrigger * border222 = new borderTrigger(1,"+79212222222",123,2);
                 locator.addTrigger(border222);
                locator.setSubscriberLocation("+79211111111", 10, 20);
                locator.setSubscriberLocation("+79212222222", 1, 2);
                auto subscribers = locator.getSubsciberInZone(123);
                ASSERT_EQ(subscribers.size(), 1);

                locator.setSubscriberLocation("+79212222222", 11, 12);
            }

            TEST(Triggers, neartrigger){
                Locator locator;
                locator.loadJSON("settings.json");
                 AbstractTrigger * border222 = new proximityTrigger(2,"+79212222222","+79211111111",10);
                 locator.addTrigger(border222);
                locator.setSubscriberLocation("+79211111111", 10, 20);
                locator.setSubscriberLocation("+79212222222", 0, 9);

                locator.setSubscriberLocation("+79212222222", 13, 18);
            }



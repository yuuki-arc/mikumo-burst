//
//  Fragment_of_Eternity_iOS_Tests.m
//  Fragment_of_Eternity iOS Tests
//
//  Created by usr0600205 on 2014/09/09.
//
//

#import <XCTest/XCTest.h>
#include "UserDataStore.h"

@interface Fragment_of_Eternity_iOS_Tests : XCTestCase

@end

@implementation Fragment_of_Eternity_iOS_Tests

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

//- (void)testExample
//{
//    XCTFail(@"No implementation for \"%s\"", __PRETTY_FUNCTION__);
//}

- (void)testUserDataStore_rank
{
    UserDataStore::setRank(5);
    XCTAssertEqual(UserDataStore::getRank(), 5);
}

- (void)testUserDataStore_setHighScore
{
    std::vector<std::string> vector = {};
    UserDataStore::setHighScore(vector);
    UserDataStore::getHighScore();
    XCTAssertEqual(UserDataStore::getRank(), 5);
}


@end

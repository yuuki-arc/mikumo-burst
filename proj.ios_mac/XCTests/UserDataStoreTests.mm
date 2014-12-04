//#import <XCTest/XCTest.h>
//#include "UserDataStore.h"
//#include "Constant.h"
//
//USING_NS_CC;
//
//@interface UserDataStoreTests : XCTestCase
//
//@end
//
//@implementation UserDataStoreTests
//
//- (void)setUp
//{
//    [super setUp];
//    // Put setup code here. This method is called before the invocation of each test method in the class.
//}
//
//- (void)tearDown
//{
//    // Put teardown code here. This method is called after the invocation of each test method in the class.
//    [super tearDown];
//}
//
//- (std::vector<std::map<std::string, std::string>>)getScoreTable
//{
//    std::vector<std::map<std::string, std::string>> list = {};
//    
//    std::map<std::string, std::string> map;
//    map["chain"] = "200";
//    map["score"] = "12300";
//    list.push_back(map);
//    map.clear();
//    map["chain"] = "400";
//    map["score"] = "25000";
//    list.push_back(map);
//    
//    return list;
//}
//
//- (StringMapVector)getRankList
//{
//    StringMapVector list = {};
//    
//    StringMap map;
//    map["conoha"] = "100";
//    map["anzu"] = "200";
//    list.push_back(map);
//    
//    return list;
//}
//
//- (void)testSetRankList
//{
//    StringMapVector sourceList = [self getRankList];
//    UserDataStore::getInstance()->setRankList(sourceList);
//    
//    StringMapVector rankList = UserDataStore::getInstance()->getRankList();
//    for (StringMapVector::iterator it = rankList.begin(); it != rankList.end(); it++)
//    {
//        StringMap map = (*it);
//        CCLOG("conoha = %s", map["conoha"].c_str());
//        CCLOG("anzu = %s", map["anzu"].c_str());
//    }
//    
//}
//
////- (void)testGetRankList
////{
////    //    std::vector<std::string> vector = {};
////    //    UserDataStore::getInstance()->setHighScore(vector);
////    //    UserDataStore::getInstance()->getHighScore();
////    //    XCTAssertEqual(UserDataStore::getInstance()->getRank(), 5);
////    XCTAssertEqual(UserDataStore::getInstance()->getRank(), 5);
////}
//
//
////- (void)testSetRank
////{
////    UserDataStore::getInstance()->setRank(20);
////    UserDefault* userDefault = UserDefault::getInstance();
////    int rank = userDefault->getIntegerForKey(Constant::UserDefaultKey::RANK(), 0);
////    XCTAssertEqual(rank, 20);
////}
////
////- (void)testGetRank
////{
////    UserDefault* userDefault = UserDefault::getInstance();
////    userDefault->setIntegerForKey(Constant::UserDefaultKey::RANK(), 10);
////    XCTAssertEqual(UserDataStore::getInstance()->getRank(), 10);
////}
//
////- (void)testSetScoreTable
////{
////    UserDefault* userDefault = UserDefault::getInstance();
////    
////    std::vector<std::map<std::string, std::string>> list = [self getScoreTable];
////    
////    UserDataStore::getInstance()->setScoreTable(list);
////    std::string rank = userDefault->getStringForKey(Constant::UserDefaultKey::SCORE_TABLE(), "");
////    XCTAssertEqual(UserDataStore::getInstance()->getRank(), 5);
////    
////    //    CCLOG(UserDataStore::getInstance()->getHighScore());
////    //    XCTAssertEqual(UserDataStore::getInstance()->getRank(), 5);
////}
////
////- (void)testGetScoreTable
////{
////    //    std::vector<std::string> vector = {};
////    //    UserDataStore::getInstance()->setHighScore(vector);
////    //    UserDataStore::getInstance()->getHighScore();
////    //    XCTAssertEqual(UserDataStore::getInstance()->getRank(), 5);
////    XCTAssertEqual(UserDataStore::getInstance()->getRank(), 5);
////}
//
//@end

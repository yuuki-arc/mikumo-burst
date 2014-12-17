/*
 * RPG風文字送り＆ページ送りをするラベル
 *
 * 検証バージョン cocos2d-x v3.1
 *
 * 更新履歴
 * 2014.06.28  cocos2d-x v3.1 対応 (warning対応)
 * 2014.03.17  cocos2d-x v3.0 rc0 対応
 * 2014.03.10  cocos2d-x v3.0 rc 対応
 *             キーワードの文字サイズ指定は機能廃止
 * 2014.03.08  ページ送りのコールバックを追加。
 * 2014.03.07  DisplaySpeedプロパティに0を設定した場合は一括表示するようにしました
 * 2014.03.06  追加
 * 
 */

#include "cocos2d.h"

struct KeywordDataSet {
    std::string word;
    cocos2d::Color3B strongColor;
    //    float scaleTo;    廃止
};

class LabelAttributedBMFont : public cocos2d::Label
{
    
public:
    LabelAttributedBMFont(cocos2d::FontAtlas *atlas = nullptr,
                          cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::LEFT,
                          cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP,
                          bool useDistanceField = false,
                          bool useA8Shader = false);
    
    virtual ~LabelAttributedBMFont();
    
    // 何フレーム周期で文字送りをするか
    CC_SYNTHESIZE(unsigned int, m_dispCycle, DispCycle);
    
    // 文字送りする際は何文字ずつ行うか (0を設定した場合は常に一括表示に。ただしページ送りやキーワード強調は有効)
    CC_SYNTHESIZE(unsigned int, m_dispSpeed, DispSpeed)
    
    // 文字送りが完了状態かどうか
    CC_SYNTHESIZE(bool, m_isAllCharDisplayed, IsAllCharDisplayed);
    
    
    /**
     文字色、文字サイズを局所的に変更したいキーワードを追加する
     @param keyword   キーワード
     @param fontColor キーワードの色
     @param fontScale キーワードのサイズ  廃止
     */
    void addKeyWord(std::string keyword, cocos2d::Color3B fontColor/*, float fontScale*/);
    
    /**
     キーワードを削除する
     @param 削除したいキーワード
     */
    void removeKeyWord(std::string keyword);
    
    /**
     文字送り中の文字を全て表示させる
     */
    void dispAllCharacters();
    
    virtual void update(float dt);
    
    static LabelAttributedBMFont* createWithBMFont(const std::string& bmfontFilePath, const std::string &text,
                                                   const cocos2d::TextHAlignment& alignment = cocos2d::TextHAlignment::LEFT, int lineWidth = 0,
                                                   const cocos2d::Point& imageOffset = cocos2d::Point::ZERO);
    
    static LabelAttributedBMFont* createWithBMFont(const std::string& bmfontFilePath, const std::vector< std::string > pages,
                                                   const cocos2d::TextHAlignment& alignment = cocos2d::TextHAlignment::LEFT, int lineWidth = 0,
                                                   const cocos2d::Point& imageOffset = cocos2d::Point::ZERO);
    
    virtual void initWithPages(const std::vector< std::string > &pages/*, const std::string& fntFile, float width = -1, cocos2d::TextHAlignment alignment = cocos2d::TextHAlignment::LEFT, cocos2d::Point imageOffset = cocos2d::Point::ZERO*/);
    void start();       // 文字送りスタート
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void updateColor();
    void setPages(const std::vector< std::string > &pages);
    void setCallback( const std::function<void(cocos2d::Ref*)> &callback );
    void setCallbackChangedPage( const std::function<void( int )> &callback );
    
    virtual void setString(const std::string &text, bool isRest);
    
protected:
    
    std::vector< std::string > m_pages;
    std::vector< std::string >::iterator m_iterator;
    std::function<void(Ref*)>  m_callback;
    std::function<void(int)>  m_callbackChangedPage;
    std::map< int, cocos2d::Color3B > m_colorsMatchingWord;
    
private:
    
    std::list< KeywordDataSet > m_keyWords;
    
    /**
     キーワードの存在する位置を検出する
     */
    void searchKeywordsIndex(std::string targetString);
    
    /**
     ラベル上の文字色、文字サイズを初期化する
     */
    void initKeyWordsVisualInfo();
    
};

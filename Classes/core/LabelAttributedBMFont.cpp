
#include "LabelAttributedBMFont.h"

USING_NS_CC;
using namespace std;


#define NEWLINE_CHAR    "\n"
#define NULL_CHAR       ""


LabelAttributedBMFont::LabelAttributedBMFont(cocos2d::TextHAlignment hAlignment,
                                             cocos2d::TextVAlignment vAlignment)
:Label::Label(hAlignment, vAlignment)
{
    
}

LabelAttributedBMFont::~LabelAttributedBMFont()
{
    log("LabelAttributedBMFont ~LabelAttributedBMFont()");
}

LabelAttributedBMFont* LabelAttributedBMFont::createWithBMFont(const std::string& bmfontFilePath, const std::string &text,
                                                               const cocos2d::TextHAlignment& alignment, int lineWidth,
                                                               const cocos2d::Point& imageOffset)
{
    vector< string >pages;
    pages.push_back(text);
    
    return LabelAttributedBMFont::createWithBMFont(bmfontFilePath, pages, alignment, lineWidth, imageOffset);
}

LabelAttributedBMFont* LabelAttributedBMFont::createWithBMFont(const std::string& bmfontFilePath, std::vector< std::string > pages,
                                                               const cocos2d::TextHAlignment& alignment, int lineWidth,
                                                               const cocos2d::Point& imageOffset)
{
    LabelAttributedBMFont *ret = new LabelAttributedBMFont(alignment);
    
    if (!ret)
        return nullptr;
    
    if (ret->setBMFontFilePath(bmfontFilePath, imageOffset))
    {
        ret->setMaxLineWidth(lineWidth);
        ret->initWithPages(pages);
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        return nullptr;
    }
}

void LabelAttributedBMFont::initWithPages(const std::vector< std::string > &pages/*, const std::string& fntFile, float width, cocos2d::TextHAlignment alignment, cocos2d::Point imageOffset*/)
{
	m_dispSpeed = 1;
	m_dispCycle = 5;
	m_isAllCharDisplayed = false;
    
    setPages(pages);
    
    // touch event
    auto listner = EventListenerTouchOneByOne::create();
    listner->setSwallowTouches(true);
    listner->onTouchBegan = CC_CALLBACK_2(LabelAttributedBMFont::onTouchBegan, this);
    listner->onTouchEnded = CC_CALLBACK_2(LabelAttributedBMFont::onTouchEnded, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listner, this);
    
}

void LabelAttributedBMFont::start()
{
    unscheduleUpdate();
    if (m_dispSpeed == 0) {
        dispAllCharacters();
        return;
    }
    m_isAllCharDisplayed = false;
    scheduleUpdate();
}

void LabelAttributedBMFont::setPages(const std::vector<std::string> &pages)
{
    m_pages.clear();
    for (int i = 0; i < pages.size(); i++) {
        m_pages.push_back(pages[i]);
    }
    m_iterator = m_pages.begin();
    
    setString("", true);
}

void LabelAttributedBMFont::setCallback(const std::function<void (cocos2d::Ref *)> &callback)
{
    m_callback = callback;
}

void LabelAttributedBMFont::setCallbackChangedPage(const std::function<void (int)> &callback)
{
    m_callbackChangedPage = callback;
}

void LabelAttributedBMFont::setString(const std::string &text, bool isRest)
{
    Label::setString(text);
    if (! isRest) {
        return;
    }
    //    resetCurrentString();
    updateContent();
    
    m_isAllCharDisplayed = false;
    searchKeywordsIndex(m_pages.at(m_iterator - m_pages.begin()));
    
}

bool LabelAttributedBMFont::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return true;
}

void LabelAttributedBMFont::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    // 全ページ表示後なら
    if (m_iterator == m_pages.end()) {
        log("LabelAttributedBMFont : fin");
        return;
    }
    
    // 文字送りがおわってなかったら
    if (! this->getIsAllCharDisplayed()) {
        this->dispAllCharacters();
        return;
    }
    
    m_iterator++;
    if (m_iterator == m_pages.end()) {
        log("LabelAttributedBMFont : callback");
        if (m_callback) m_callback(this);
        return;
    }
    
    setString("", true);    // 表示は初期化
    
    if (m_callbackChangedPage) {
        auto dif = m_iterator - m_pages.begin();
        m_callbackChangedPage(dif);
    }
    
    start();
}

void LabelAttributedBMFont::updateColor()
{
//    if (nullptr == _textureAtlas)
//    {
//        return;
//    }
    
    Color4B color4( _displayedColor.r, _displayedColor.g, _displayedColor.b, _displayedOpacity );
    
    // special opacity for premultiplied textures
    if (_isOpacityModifyRGB)
    {
        color4.r *= _displayedOpacity/255.0f;
        color4.g *= _displayedOpacity/255.0f;
        color4.b *= _displayedOpacity/255.0f;
    }
    
    cocos2d::TextureAtlas* textureAtlas;
    V3F_C4B_T2F_Quad *quads;
    for (const auto& batchNode:_batchNodes)
    {
        
        textureAtlas = batchNode->getTextureAtlas();
        quads = textureAtlas->getQuads();
        auto count = textureAtlas->getTotalQuads();
        
        for (int index = 0; index < count; ++index)
        {
            // 指定文字が強調色指定されているかどうか
            if (m_colorsMatchingWord.find(index) != m_colorsMatchingWord.end()) {
                auto customColor = Color4B( m_colorsMatchingWord.at(index) );
                if (_isOpacityModifyRGB)
                {
                    customColor.r *= _displayedOpacity/255.0f;
                    customColor.g *= _displayedOpacity/255.0f;
                    customColor.b *= _displayedOpacity/255.0f;
                }
                quads[index].bl.colors = customColor;
                quads[index].br.colors = customColor;
                quads[index].tl.colors = customColor;
                quads[index].tr.colors = customColor;
            } else {
                quads[index].bl.colors = color4;
                quads[index].br.colors = color4;
                quads[index].tl.colors = color4;
                quads[index].tr.colors = color4;
            }
            textureAtlas->updateQuad(&quads[index], index);
        }
    }
}

/**
 文字色、文字サイズを局所的に変更したいキーワードを追加する
 @param keyword   キーワード
 @param fontColor キーワードの色
 @param fontScale キーワードのサイズ  廃止
 */
void LabelAttributedBMFont::addKeyWord(string keyword, Color3B fontColor/*, float fontScale*/)
{
	// 改行コードの場合は何もしない
	if (keyword == NEWLINE_CHAR) {
		log("LabelAttributedBMFont addKeyWord() keyword is newline character!!!");
		return;
	}
    
	KeywordDataSet dataset;
    dataset.word = keyword;
    dataset.strongColor = fontColor;
    //    dataset.scaleTo = fontScale;      廃止
    
    m_keyWords.push_back(dataset);
    
    // キーワードに該当する文字があるか検索
    searchKeywordsIndex(*m_iterator);
}

/**
 キーワードを削除する
 @param 削除したいキーワード
 */
void LabelAttributedBMFont::removeKeyWord(string keyword)
{
    auto it = m_keyWords.begin();
    while (it != m_keyWords.end()) {
        auto &dataset = *it;
        if (dataset.word != keyword) {
            it++;
            continue;
        }
        m_keyWords.erase(it);
        return;
    }
    log("LabelAttributedBMFont not found keyword:%s", keyword.c_str());
	
}

/**
 文字列の置換
 @param targetStr 置換をかける文字列
 @param fromStr   置換対象文字列
 @param toStr     置換後文字列
 @return          置換完了後文字列
 */
string replace(string &targetStr, string fromStr, string toStr)
{
	string::size_type pos = targetStr.find_first_of(fromStr, 0);
	while (string::npos != pos) {
		targetStr.replace(pos, string(fromStr).length(), toStr);
		pos = targetStr.find_first_of(fromStr, pos);
	}
	return targetStr;
}

/**
 検索情報初期化
 */
void LabelAttributedBMFont::initKeyWordsVisualInfo()
{
    m_colorsMatchingWord.clear();
}

/**
 文字送り中の文字を全て表示させる
 */
void LabelAttributedBMFont::dispAllCharacters()
{
    if (m_isAllCharDisplayed) {
        return;
    }
    m_isAllCharDisplayed = true;
    unscheduleUpdate();
    
    auto line = *m_iterator;
    setString(line, false);
}

/**
 キーワードの存在する位置を検出する
 */
void LabelAttributedBMFont::searchKeywordsIndex(std::string targetString)
{
	// 改行コードを除去
	targetString = replace(targetString, NEWLINE_CHAR, NULL_CHAR);
    
    if (targetString.empty()) {
        return;
    }
    
	// 文字色、文字サイズを初期化
	initKeyWordsVisualInfo();
    
    auto it = m_keyWords.begin();
	// 登録したキーワード分だけ検索処理を行う
    while (it != m_keyWords.end()) {
		auto &dataset = *it;
        auto key = dataset.word;
        u16string u16key;
        StringUtils::UTF8ToUTF16(key.c_str(), u16key);
        unsigned long keyLengthMultiByte = u16key.length();     // キーワードの長さ(マルチバイト)
		unsigned long searchIndex = 0;                                                   // 現在の検出走査位置
		unsigned long keyFindIndex = targetString.find(key, searchIndex);                // キーワードが検出された位置
        
		while (keyFindIndex != string::npos) {
			unsigned long keyFindIndexMultiByte = 0;                         // キーワードが検出された位置(マルチバイト)
			// キーワードが検出された位置(マルチバイト)を検出
			string clipStr = targetString.substr(0, keyFindIndex);
            u16string u16ClipStr;
            StringUtils::UTF8ToUTF16(clipStr, u16ClipStr);
            keyFindIndexMultiByte = u16ClipStr.length();
            
            for (unsigned int i = 0; i < keyLengthMultiByte; i++) {
                long index = keyFindIndexMultiByte + i;
                m_colorsMatchingWord[(int)index] = dataset.strongColor;
            }
            
			// 現在の検出走査位置をキーワード終了位置へ
			searchIndex = (keyFindIndex + key.length());
            
			// キーワード終了位置以降に存在するキーワードを検出
			keyFindIndex = targetString.find(key, searchIndex);
		}
        
        it++;
	}
}

/**
 更新、文字送りを行う
 表示している文字インデックスを進めて、文字を再設定することで実現
 @param dt 前回コールされてからの経過時間
 */
void LabelAttributedBMFont::update(float dt)
{
    
    if (m_dispSpeed == 0) {
        dispAllCharacters();
        return;
    }
    
    
    auto line = m_pages.at(m_iterator - m_pages.begin());
    u16string u16Line;
    StringUtils::UTF8ToUTF16(line.c_str(), u16Line);
    long len = u16Line.length();
    int currentLen = getStringLength();
    
    if (currentLen >= len) {
        m_isAllCharDisplayed = true;
        unscheduleUpdate();
        return;
    }
    
	if (Director::getInstance()->getTotalFrames() % m_dispCycle != 0) {
        return;
    }
    
    auto newLen = len < (currentLen + m_dispSpeed) ? len - currentLen : currentLen + m_dispSpeed;
    std::u16string u16NewLine;
    
    for (int i = 0; i < newLen; ++i)
    {
        u16NewLine.push_back(u16Line[i]);
    }
    
    string newStr;
    StringUtils::UTF16ToUTF8(u16NewLine, newStr);
    setString(newStr, false);
    
	
}



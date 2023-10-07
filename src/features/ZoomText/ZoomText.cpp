#include "ZoomText.hpp"

void showZoomText(EditorUI* ui) {
    if (Mod::get()->template getSettingValue<bool>("show-zoom-text")) {
        auto label = static_cast<CCLabelBMFont*>(ui->getChildByID("zoom-text"_spr));

        if (label) {
            label->setString(
                ("Zoom: " + numToString(
                    ui->m_editorLayer->m_objectLayer->getScale(), 2
                ) + "x").c_str()
            );
            label->setOpacity(255);
            label->stopAllActions();
            label->runAction(CCSequence::create(
                CCDelayTime::create(.5f),
                CCFadeOut::create(.5f),
                nullptr
            ));
        }
    }
}

class $modify(EditorUI) {
    bool init(LevelEditorLayer* layer) {
        if (!EditorUI::init(layer))
            return false;
        
        auto winSize = CCDirector::sharedDirector()->getWinSize();

        auto zoomLabel = CCLabelBMFont::create("", "bigFont.fnt");
        zoomLabel->setScale(.5f);
        zoomLabel->setPosition(winSize.width / 2, winSize.height - 60.f);
        zoomLabel->setID("zoom-text"_spr);
        zoomLabel->setOpacity(0);
        zoomLabel->setZOrder(99999);
        this->addChild(zoomLabel);

        return true;
    }

    void updateZoom(float zoom) {
        EditorUI::updateZoom(zoom);
        showZoomText(this);
    }
};

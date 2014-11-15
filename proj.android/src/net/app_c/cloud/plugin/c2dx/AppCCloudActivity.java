package net.app_c.cloud.plugin.c2dx;

import net.app_c.cloud.sdk.AppCMatchApp.OnAppCMatchAppListener;
import org.cocos2dx.lib.Cocos2dxActivity;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.os.Bundle;

/**
 * AppCCloudActivity メインとなるActivityはこのActivityを継承してください appC cloud Plugin
 * Cocos2d-x
 * 
 * @author cayto inc.
 */
public class AppCCloudActivity extends Cocos2dxActivity implements OnAppCMatchAppListener {
	static final String TAG = "AppActivity";

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		AppCCloudPlugin.setActivity(this);
	}

	@Override
	public void onConfigurationChanged(Configuration newConfig) {
		super.onConfigurationChanged(newConfig);
		// configurationChanged処理
		AppCCloudPlugin.configurationChanged();
	}

	@Override
	public void finish() {
		super.finish();
		// appC cloud Plugin finish
		AppCCloudPlugin.finish();
	}

	@Override
	protected void onResume() {
		super.onResume();
		// カットイン初期化
		AppCCloudPlugin.initCutin();
		// MatchAppリフレッシュ
		AppCCloudPlugin.refreshMatchApp();
	}

	/**
	 * MatchAppコールバック
	 */
	@Override
	public void onMatchAppCreateLayout(String arg0, String arg1, String arg2, Bitmap arg3, final Bitmap banner) {
		// マッチアップ表示(バナー)
		AppCCloudPlugin.setMatchAppBannerView(banner);
	}
}

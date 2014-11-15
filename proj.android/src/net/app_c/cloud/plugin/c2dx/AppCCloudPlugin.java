package net.app_c.cloud.plugin.c2dx;

import java.util.ArrayList;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import net.app_c.cloud.sdk.AppCCloud;
import net.app_c.cloud.sdk.AppCCloud._Data.DataStore;
import net.app_c.cloud.sdk.AppCCloud._Gamers.LeaderBoard;
import net.app_c.cloud.sdk.AppCMarqueeView;
import net.app_c.cloud.sdk.AppCMoveIconView;
import net.app_c.cloud.sdk.AppCRecBannerView;
import net.app_c.cloud.sdk.AppCSimpleView;
import org.json.JSONArray;
import org.json.JSONObject;
import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.ImageButton;
import android.widget.ImageView;

/**
 * AppCCloudPlugin.
 * 
 * zappC cloud Plugin Cocos2d-x.
 * 
 * @author cayto inc.
 */
public final class AppCCloudPlugin {

	private static final String TAG = "c2dx";

	public static boolean sStartedFlg = false;

	private static AppCCloud appCCloud = null;
	private static Activity sActivity = null;
	private static FrameLayout sAdCLayout = null;
	private static AppCSimpleView sSimpleView = null;
	private static AppCMarqueeView sMarqueeView = null;
	private static AppCMoveIconView sMoveIconView = null;
	private static ImageView sMatchAppBannerView = null;
	private static AppCRecBannerView sRecBannerView = null;

	private static int options;
	private final static int START_TIMEOUT_MSEC = 30 * 1000;

	// 起動オプション
	final static int API_AD = 0x00000000;
	final static int API_GAMERS = 0x00000001;
	final static int API_PUSH = 0x00000010;
	final static int API_DATA = 0x00000100;
	final static int API_PURCHASE = 0x00001000;
	final static int API_REWARD = 0x00010000;

	public static void setActivity(Activity activity) {
		sActivity = activity;
		sAdCLayout = new FrameLayout(activity);
		activity.addContentView(sAdCLayout, new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT,
				FrameLayout.LayoutParams.MATCH_PARENT));
		// Log.d("appC", "call setActivity");
	}

	/**
	 * オプション設定 startの前に呼んでください。
	 * 
	 * @param options_
	 */
	public static void setOptions(int opts) {
		options = opts;
		// Log.d("appC", "call setOptions");
	}

	/**
	 * 初期化とその完了待ちを行う。
	 * 
	 * @param options
	 * @return TRUE : 正常に完了した。　FALSE:初期化でタイムアウト発生
	 */
	public static boolean start() {
		// Log.d("appC", "call start");
		final CountDownLatch latch = new CountDownLatch(1);
		final int _options = options;
		try {
			sActivity.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					appCCloud = new AppCCloud(sActivity, new AppCCloud.OnAppCCloudStartedListener() {
						@Override
						public void onAppCCloudStarted(boolean flg) {
							sStartedFlg = flg;
							latch.countDown();
							// Log.d("appC", "on started " + flg);
						}
					});
					if ((_options & API_DATA) != 0) {
						// data store on
						appCCloud.on(AppCCloud.API.DATA);
					}
					if ((_options & API_GAMERS) != 0) {
						// gamers on
						appCCloud.on(AppCCloud.API.GAMERS);
					}
					if ((_options & API_PURCHASE) != 0) {
						// purchase on
						appCCloud.on(AppCCloud.API.PURCHASE);
					}
					if ((_options & API_PUSH) != 0) {
						// push on
						appCCloud.on(AppCCloud.API.PUSH);
					}
					if ((_options & API_REWARD) != 0) {
						// reward on
						appCCloud.on(AppCCloud.API.REWARD);
					}
					appCCloud.start();
				}
			});
		} catch (Exception e) {
			Log.e(TAG, "error", e);
			return false;
		}
		try {
			latch.await(START_TIMEOUT_MSEC, TimeUnit.SECONDS);
		} catch (InterruptedException e) {
			Log.e(TAG, "error", e);
			return false;
		}
		// カットインで初期化
		initCutin();
		return sStartedFlg;
	}

	/**
	 * configurationChanged.
	 */
	public static void configurationChanged() {
		// カットイン初期化
		initCutin();
		// マッチアップリフレッシュ
		refreshMatchApp();
		// ムーヴアイコン再表示
		if (sMoveIconView != null) {
			MoveIconViewInfo info = (MoveIconViewInfo)sMoveIconView.getTag();
			hideMoveIconView();
			showMoveIconView(info.horizon, info.vertical, info.skinColor, info.textColor);
		}
	}

	/**
	 * appC cloud Plugin finish.
	 */
	public static void finish() {
		if (appCCloud != null) {
			appCCloud.finish();
			try {
				Thread.sleep(500);
			} catch (InterruptedException e) {
			}
			appCCloud = null;
			sStartedFlg = false;
		}
	}

	/**
	 * 広告リスト型表示.
	 */
	public static void callAdListActivity() {
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (appCCloud == null) {
					// Log.w(TAG,"plugin was not initialized");
					return;
				}
				appCCloud.Ad.callWebActivity();
			}
		});
	}

	/**
	 * シンプル表示.
	 * 
	 * @param vertical
	 * @param skinColor
	 * @param textColor
	 */
	public static void showSimpleView(final int vertical, final String skinColor, final String textColor) {
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (appCCloud == null) {
					// Log.w(TAG,"plugin was not initialized");
					return;
				}
				removeView(sSimpleView);
				clearImage(sSimpleView);
				sSimpleView = appCCloud.Ad.loadSimpleView(skinColor, textColor);
				sSimpleView.setGravity(cnvGravityVertical(vertical));
				sAdCLayout.addView(sSimpleView);
			}
		});
	}

	/**
	 * シンプル非表示.
	 */
	public static void hideSimpleView() {
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				removeView(sSimpleView);
				clearImage(sSimpleView);
				sSimpleView = null;
			}
		});
	}

	/**
	 * ムーヴアイコン型表示.
	 * 
	 * @param vertical
	 * @param horizontal
	 * @param skinColor
	 * @param textColor
	 */
	public static void showMoveIconView(final int horizontal, final int vertical, final String skinColor, final String textColor) {
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (appCCloud == null) {
					// Log.w(TAG,"plugin was not initialized");
					return;
				}
				removeView(sMoveIconView);
				sMoveIconView = appCCloud.Ad.loadMoveIconView(skinColor, textColor);
				sMoveIconView.setGravity(cnvGravityHorizon(horizontal) | cnvGravityVertical(vertical));
				sAdCLayout.addView(sMoveIconView);
				sMoveIconView.setTag(new MoveIconViewInfo(horizontal, vertical, skinColor, textColor));
			}
		});
	}

	/**
	 * ムーヴアイコン型非表示.
	 */
	public static void hideMoveIconView() {
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (appCCloud == null) {
					// Log.w(TAG,"plugin was not initialized");
					return;
				}
				removeView(sMoveIconView);
				clearImage(sMoveIconView);
				sMoveIconView = null;
			}
		});
	}

	/**
	 * マーキー型表示.
	 * 
	 * @param vertical
	 * @param textColor
	 */
	public static void showMarqueeView(final int vertical, final String textColor) {
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (appCCloud == null) {
					// Log.w(TAG,"plugin was not initialized");
					return;
				}
				removeView(sMarqueeView);
				sMarqueeView = appCCloud.Ad.loadMarqueeView(textColor);
				sMarqueeView.setGravity(cnvGravityVertical(vertical));
				sAdCLayout.addView(sMarqueeView);
			}
		});
	}

	/**
	 * マーキー型非表示.
	 */
	public static void hideMarqueeView() {
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				removeView(sMarqueeView);
				clearImage(sMarqueeView);
				sMarqueeView = null;
			}
		});
	}

	/**
	 * カットイン型初期化.
	 */
	static void initCutin() {
		if (!sStartedFlg) {
			// Log.w(TAG,"Plugin was not started.");
			return;
		}
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (appCCloud == null) {
					// Log.w(TAG,"Plugin was not started.");
					return;
				}
				appCCloud.Ad.initCutin();
			}
		});
	}

	/**
	 * カットイン型表示.
	 */
	public static void callCutin() {
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (appCCloud == null) {
					// Log.w(TAG,"Plugin was not started.");
					return;
				}
				appCCloud.Ad.callCutin();
			}
		});
	}

	/**
	 * カットイン型表示.(アプリケーション終了ボタン付き)
	 */
	public static void callCutinFinish() {
		try {
			if (appCCloud == null || !sStartedFlg) {
				// Log.w(TAG,"Plugin was not started.");
				return;
			}
			sActivity.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					if (appCCloud == null) {
						// Log.w(TAG,"Plugin was not started.");
						return;
					}
					appCCloud.Ad.callCutinFinish(true);
				}
			});
		} catch (Exception exception) {
		}
	}

	/**
	 * マッチアップ表示(バナー).
	 * 
	 * @param horizon
	 * @param vertica
	 */
	public static void showMatchAppBannerView(final int horizon, final int vertical) {
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (appCCloud == null) {
					// Log.w(TAG,"Plugin was not started.");
					return;
				}
				removeView(sMatchAppBannerView);
				sMatchAppBannerView = new ImageView(sActivity);
				appCCloud.Ad.setMatchAppView(sMatchAppBannerView);
				FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.WRAP_CONTENT,
						FrameLayout.LayoutParams.WRAP_CONTENT);
				params.gravity = cnvGravityHorizon(horizon) | cnvGravityVertical(vertical);
				sAdCLayout.addView(sMatchAppBannerView, params);
			}
		});
	}

	/**
	 * マッチアップ非表示(バナー).
	 */
	public static void hideMatchAppBannerView() {
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (appCCloud == null) {
					// Log.w(TAG,"Plugin was not started.");
					return;
				}
				removeView(sMatchAppBannerView);
				clearImage(sMatchAppBannerView);
				sMatchAppBannerView = null;
			}
		});
	}

	/**
	 * マッチアップリフレッシュ.
	 */
	static void refreshMatchApp() {
		if (!sStartedFlg) {
			return;
		}
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (appCCloud == null) {
					// Log.w(TAG,"Plugin was not started.");
					return;
				}
				appCCloud.Ad.refreshMatchApp();
			}
		});
	}

	/**
	 * マッチアップ(バナー)表示. コールバックから呼び出される
	 * 
	 * @param banner
	 */
	static void setMatchAppBannerView(final Bitmap banner) {
		if (sMatchAppBannerView == null) {
			return;
		}
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				try {
					if (appCCloud == null) {
						// Log.w(TAG,"Plugin was not started.");
						return;
					}
					if (banner != null) {
						sMatchAppBannerView.setImageDrawable(new BitmapDrawable(sActivity.getResources(), banner));
					}
				} catch (Exception e) {
				}
			}
		});
	}

	/**
	 * リコネクトバナー表示.
	 * 
	 * @param vertical
	 */
	public static void showRecBannerView(final int vertical) {
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (appCCloud == null) {
					// Log.w(TAG,"plugin was not initialized");
					return;
				}
				removeView(sRecBannerView);
				sRecBannerView = appCCloud.Ad.loadRecBannerView();
				FrameLayout.LayoutParams layoutParams =
						new FrameLayout.LayoutParams(FrameLayout.LayoutParams.WRAP_CONTENT, FrameLayout.LayoutParams.WRAP_CONTENT, cnvGravityVertical(vertical));
				sAdCLayout.addView(sRecBannerView, layoutParams);
			}
		});
	}

	/**
	 * リコネクトバナー非表示.
	 */
	public static void hideRecBannerView() {
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				removeView(sRecBannerView);
				clearImage(sRecBannerView);
				sRecBannerView = null;
			}
		});
	}

	/**
	 * リコネクトインタースティシャル表示.
	 */
	public static void callRecInterstitial() {
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (appCCloud == null) {
					// Log.w(TAG,"Plugin was not started.");
					return;
				}
				appCCloud.Ad.callRecInterstitial();
			}
		});
	}

	/**
	 * リコネクトインタースティシャル(終了)表示.
	 */
	public static void callRecInterstitialFinish() {
		try {
			if (appCCloud == null || !sStartedFlg) {
				// Log.w(TAG,"Plugin was not started.");
				return;
			}
			sActivity.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					if (appCCloud == null) {
						// Log.w(TAG,"Plugin was not started.");
						return;
					}
					appCCloud.Ad.callRecInterstitialFinish();
				}
			});
		} catch (Exception exception) {
		}
	}

	/**
	 * viewを全て非表示.
	 */
	public static void hideAllAdViews() {
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (appCCloud == null) {
					// Log.w(TAG,"Plugin was not started.");
					return;
				}
				sAdCLayout.removeAllViews();
				clearImage(sSimpleView);
				clearImage(sMarqueeView);
				clearImage(sMoveIconView);
				clearImage(sMatchAppBannerView);
				clearImage(sRecBannerView);
				sSimpleView = null;
				sMarqueeView = null;
				sMoveIconView = null;
				sMatchAppBannerView = null;
				sRecBannerView = null;
			}
		});
	}

	/**
	 * 広告前面確認.
	 * 
	 * @return true:前面　false:後面
	 */
	public static boolean IsForegroundAd() {
		return appCCloud.Ad.isWebActivity() || appCCloud.Ad.isCutinView() || appCCloud.Ad.isRecInterstitial();
	}

	/**
	 * inc play count.
	 */
	public static void incPlayCount() {
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (appCCloud == null) {
					// Log.w(TAG,"Plugin was not started.");
					return;
				}
				appCCloud.Gamers.incPlayCount();
			}
		});
	}

	/**
	 * play count 取得.
	 * 
	 * @return play count
	 */
	public static int getPlayCount() {
		return appCCloud.Gamers.getPlayCount();
	}

	/**
	 * leader board設定.
	 * 
	 * @param id
	 * @param score
	 */
	public static void setLeaderBoard(final int id, final int score) {
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (appCCloud == null) {
					// Log.w(TAG,"Plugin was not started.");
					return;
				}
				appCCloud.Gamers.setLeaderBoard(id, score);
			}
		});
	}

	/**
	 * leader board設定.
	 * 
	 * @param id
	 * @param value
	 */
	public static void setLeaderBoard(final int id, final float score) {
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (appCCloud == null) {
					// Log.w(TAG,"Plugin was not started.");
					return;
				}
				appCCloud.Gamers.setLeaderBoard(id, score);
			}
		});
	}

	/**
	 * leader board取得.
	 * 
	 * @param id
	 * @return leaderBoard json
	 */
	public static String getLeaderBoard(final int id) {
		LeaderBoard leaderBoard = appCCloud.Gamers.getLeaderBoard(id);
		JSONObject json = new JSONObject();
		try {
			Integer idVal = leaderBoard.getId();
			json.put("id", idVal.toString());
			json.put("name", leaderBoard.getName());
			json.put("score", leaderBoard.getScore());
			json.put("time", leaderBoard.getTime());
		} catch (Exception e) {
		}
		return json.toString();
	}

	/**
	 * gamers view表示.
	 */
	public static void showGamersView() {
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (appCCloud == null) {
					// Log.w(TAG,"Plugin was not started.");
					return;
				}
				appCCloud.Gamers.callGamersActivity();
			}
		});
	}

	/**
	 * active lb 設定
	 * 
	 * @param ids
	 */
	public static void setActiveLeaderBoards(String[] ids) {
		// int
		int count = ids.length;
		Integer[] lbIds = new Integer[count];
		for (int i = 0; i < count; i++) {
			lbIds[i] = Integer.valueOf(ids[i]);
		}
		appCCloud.Gamers.setActiveLeaderBoards(lbIds);
	}

	/**
	 * data store 保存
	 * 
	 * @param id
	 * @param val
	 */
	public static void setDataStore(String id, int val) {
		appCCloud.Data.set(id, val);
	}

	/**
	 * data store 保存
	 * 
	 * @param id
	 * @param text
	 */
	public static void setDataStore(String id, String text) {
		appCCloud.Data.set(id, text);
	}

	/**
	 * data store 取得.
	 * 
	 * @param id
	 * @return DataStore json
	 */
	public static String getDataStore(String id) {
		DataStore dataStore = appCCloud.Data.getDataStore(id);
		JSONObject json = new JSONObject();
		try {
			json.put("key", dataStore.getId());
			json.put("val", dataStore.getVal() == null ? 0 : dataStore.getVal());
			json.put("text", dataStore.getText() == null ? "" : dataStore.getText());
		} catch (Exception e) {
		}
		return json.toString();
	}

	/**
	 * item数追加
	 * 
	 * @param id
	 * @param addCount
	 */
	public static void addItemCount(String id, int addCount) {
		if (appCCloud == null) {
			// Log.w(TAG,"Plugin was not started.");
			return;
		}
		appCCloud.Purchase.addItemCount(id, addCount);
	}

	/**
	 * item数設定
	 * 
	 * @param id
	 * @param count
	 */
	public static void setItemCount(String id, int count) {
		if (appCCloud.Purchase != null) {
			appCCloud.Purchase.setItemCount(id, count);
		}
	}

	/**
	 * item数取得
	 * 
	 * @param id
	 * @return
	 */
	public static int getItemCount(String id) {
		return appCCloud.Purchase.getItemCount(id);
	}

	/**
	 * アイテムSTORE表示
	 */
	public static void openPurchaseView() {
		if (appCCloud == null) {
			// Log.w(TAG,"Plugin was not started.");
			return;
		}
		appCCloud.Purchase.callPurchaseActivity();
	}

	/**
	 * アイテム取得
	 * 
	 * @param key
	 *            　アイテムキー
	 * @return　JSON形式文字列
	 */
	public static String getItem(String key) {
		AppCCloud._Purchase.Item item = appCCloud.Purchase.getItem(key);
		JSONObject json = new JSONObject();
		try {
			json.put("id", item.getKey());
			json.put("name", item.getName());
			json.put("count", item.getCount());
		} catch (Exception e) {
		}
		return json.toString();
	}

	/**
	 * 全アイテムを返す
	 * 
	 * @return JSON形式、getItemの戻り値が配列になったもの
	 */
	public static String getItems() {
		ArrayList<AppCCloud._Purchase.Item> items = appCCloud.Purchase.getItems();
		JSONArray jsonArray = new JSONArray();
		for (AppCCloud._Purchase.Item item : items) {
			JSONObject json = new JSONObject();
			try {
				json.put("id", item.getKey());
				json.put("name", item.getName());
				json.put("count", item.getCount());
			} catch (Exception e) {
				continue;
			}
			jsonArray.put(json);
		}
		return jsonArray.toString();
	}

	/**
	 * purchase 一覧表示
	 */
	public static void showPurchaseView() {
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				appCCloud.Purchase.callPurchaseActivity();
			}
		});
	}

	/**
	 * active item 設定
	 * 
	 * @param key
	 * @param ids
	 */
	public static void setActiveItems(String key, String[] ids) {
		appCCloud.Purchase.setActiveItems(key, ids);
	}

	/**
	 * reward point view表示.
	 */
	public static void showRewardPointView() {
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				appCCloud.Reward.callRewardPointActivity();
			}
		});
	}

	/**
	 * reward service view表示.
	 */
	public static void showRewardServiceView(final String serviceId) {
		sActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				// Log.e(TAG,"showRewardServiceView()<="+serviceId);
				appCCloud.Reward.callRewardServiceActivity(serviceId);
			}
		});
	}

	/**
	 * reward service確認.
	 */
	public static boolean isRewardService(String serviceId) {
		// Log.e(TAG,"isRewardService()<="+serviceId);
		return appCCloud.Reward.isService(serviceId);
	}

	/**
	 * reward service消去.
	 */
	public static void clearRewardService(String serviceId) {
		// Log.e(TAG,"clearRewardService()<="+serviceId);
		appCCloud.Reward.clearService(serviceId);
	}

	/**
	 * horizontalをGravityに変換.
	 * 
	 * @param horizon
	 * @return Gravity
	 */
	private static int cnvGravityHorizon(int horizon) {
		switch (horizon) {
		case 0: // LEFT
			return Gravity.LEFT;
		case 1: // CENTER
			return Gravity.CENTER_HORIZONTAL;
		case 2: // RIGHT
			return Gravity.RIGHT;
		default: // default CENTER
			return Gravity.CENTER_HORIZONTAL;
		}
	}

	/**
	 * verticalをGravityに変換
	 * 
	 * @param vertical
	 * @return Gravity
	 */
	private static int cnvGravityVertical(int vertical) {
		switch (vertical) {
		case 0: // TOP
			return Gravity.TOP;
		case 1: // BOTTOM
			return Gravity.BOTTOM;
		default: // default TOP
			return Gravity.TOP;
		}
	}

	/**
	 * ムーヴアイコン表示情報を保持するクラス
	 * 
	 * @author cayto inc.
	 */
	private static class MoveIconViewInfo {
		int horizon;
		int vertical;
		String skinColor;
		String textColor;

		MoveIconViewInfo(int horizon, int vertival, String skinColor, String textColor) {
			this.horizon = horizon;
			this.vertical = vertival;
			this.skinColor = skinColor;
			this.textColor = textColor;
		}
	}

	/**
	 * view削除
	 * 
	 * @param view
	 */
	private static void removeView(View view) {
		if (view != null) {
			try {
				// view削除
				sAdCLayout.removeView(view);
			} catch (Exception e) {
			}
		}
	}

	/**
	 * クリアイメージ.
	 * 
	 * @param view
	 */
	private static final void clearImage(View view) {
		if (view instanceof ImageButton) {
			try {
				((ImageButton)view).setImageDrawable(null);
			} catch (Exception e) {
			}
		} else if (view instanceof ImageView) {
			try {
				((ImageView)view).setImageDrawable(null);
			} catch (Exception e) {
			}
		}
		try {
			view.setBackgroundDrawable(null);
		} catch (Exception e) {
		}
		// 再帰
		if (view instanceof ViewGroup) {
			ViewGroup viewGroup = (ViewGroup)view;
			int count = viewGroup.getChildCount();
			for (int i = 0; i < count; i++) {
				clearImage(viewGroup.getChildAt(i));
			}
		}
	}
}

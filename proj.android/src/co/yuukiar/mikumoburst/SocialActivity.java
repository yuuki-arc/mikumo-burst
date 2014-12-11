package co.yuukiar.mikumoburst;

import net.app_c.cloud.plugin.c2dx.AppCCloudActivity;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;

import com.google.android.gms.analytics.HitBuilders;
import com.google.android.gms.analytics.Tracker;

public class SocialActivity extends AppCCloudActivity {

    private static Cocos2dxActivity instance = null;

	@Override
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        instance = this;
    }

    
    public static void tweet(String msg){
        Intent intent = new Intent();
        intent.setAction(Intent.ACTION_SEND);
        intent.setType("text/plain");
        intent.putExtra(Intent.EXTRA_TEXT, msg);
        instance.startActivity(Intent.createChooser(intent, "共有する"));
    }

    public static void openUrl(String url){
        Intent intent = new Intent(
            Intent.ACTION_VIEW,
            Uri.parse(url)
        );
        instance.startActivity(intent);
    }

    public static void review(String url){
        Intent intent = new Intent(
            Intent.ACTION_VIEW,
            Uri.parse("https://play.google.com/store/apps/details?id=co.yuukiar.mikumoburst&amp;hl=ja")
        );
        instance.startActivity(intent);
    }

    public static void sendScreen(String screenName) {
        // Get tracker.
        Tracker t = ((App) Cocos2dxActivity.getContext().getApplicationContext()).getTracker();
     
        // Set screen name.
        // Where path is a String representing the screen name.
        t.setScreenName(screenName);
     
        // Send a screen view.
        t.send(new HitBuilders.AppViewBuilder().build());
    }
    
    static {
        System.loadLibrary("cocos2dcpp");
    }
}

package co.yuukiar.fragmentofeternity;

import org.cocos2dx.lib.Cocos2dxActivity;
import net.app_c.cloud.plugin.c2dx.AppCCloudActivity;

import android.content.Intent;
import android.os.Bundle;

public class SocialActivity extends AppCCloudActivity {

    private static Cocos2dxActivity instance = null;

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

    static {
        System.loadLibrary("cocos2dcpp");
    }
}

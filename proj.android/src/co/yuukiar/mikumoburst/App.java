package co.yuukiar.mikumoburst;

import android.app.Application;

import co.yuukiar.mikumoburst.R;

import com.deploygate.sdk.DeployGate;
import com.google.android.gms.analytics.GoogleAnalytics;
import com.google.android.gms.analytics.Tracker;

public class App extends Application {
    @Override
    public void onCreate() {
        super.onCreate();

        // Install DeployGate to this application instance.
        DeployGate.install(this);
        
        // [[ Since DeployGate SDK r2 ]]
        //
        // If you want to prevent the app distributed by someone else,
        // specify your username explicitly here, like:
        //
        // DeployGate.install(this, "YOURUSERNAME");
    }

    Tracker mTracker;
    
    synchronized Tracker getTracker() {
        if (mTracker == null) {
            GoogleAnalytics analytics = GoogleAnalytics.getInstance(this);
            mTracker = analytics.newTracker(R.xml.ga_tracker);
        }
        return mTracker;
    }
}

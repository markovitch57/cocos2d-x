/* This file is my addition


TODO 
pdlib apparently does not use getNativeOutputSampleRate for pre openSl. So what does it use!?



LINKS
	http://stackoverflow.com/questions/11592820/writing-backwards-compatible-android-code
	pdlib - http://nettoyeur.noisepages.com/

*/


package org.cocos2dx.lib;

import android.media.AudioTrack;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.provider.Settings.Secure;
import android.util.Log;

import com.mos.mindofsound.LaunchFromWebActivity;
 
public class Cocos2dxMOS {

/*	
	// This is working version for just sample rate - before trying to incorporate new JellyBean functionality
	private static int getNativeHardwareSampleRate(int iDummy) {
		int iNativeOutputSampleRate = AudioTrack.getNativeOutputSampleRate(0);
        int iMinBufferSize = AudioTrack.getMinBufferSize(iNativeOutputSampleRate, AudioFormat.CHANNEL_OUT_STEREO ,AudioFormat.ENCODING_PCM_16BIT);//sampleRateInHz, channelConfig, audioFormat)
        
		Context context = Cocos2dxActivity.getContext();
    	if (context != null) {
			Log.d("Me","We have context!!");
		}

       // Log.d("Me","Hello from java!");
        Log.d("Me","iNativeOutputSampleRate = " + iNativeOutputSampleRate);
       // Log.d("Me","iNativeBufferFrames = " + iMinBufferSize);

		return iNativeOutputSampleRate;
	}
*/
	//static String sJavaRelaunchString = "Parameters!";

	private static int getNativeHardwareSampleRate() {
		int iNativeOutputSampleRate = 0; 
/*
		if (android.os.Build.VERSION.SDK_INT >= 17) {
			Context context = Cocos2dxActivity.getContext();
			//@TargetApi(17)  // This should prevent lint from complaining (thogh it didn't anyway!
			if (context != null) {
				AudioManager audioManager = (AudioManager)context.getSystemService(Context.AUDIO_SERVICE);
				String siNativeOutputSampleRate = audioManager.getProperty(AudioManager.PROPERTY_OUTPUT_SAMPLE_RATE);//AudioManager.PROPERTY_OUTPUT_SAMPLE_RATE); // Should requires at least 4.2.2
				iNativeOutputSampleRate = Integer.parseInt(siNativeOutputSampleRate);
				Log.d("Me","AudioManager gave native output sample rate: " + siNativeOutputSampleRate);
			}
		} 
*/		
		if (iNativeOutputSampleRate <= 0) {
			iNativeOutputSampleRate = AudioTrack.getNativeOutputSampleRate(0);
			Log.d("Me","AudioTrack.getNativeOutputSampleRate gave native output sample rate: " + iNativeOutputSampleRate);
		}
		//iMinBufferSize = AudioTrack.getMinBufferSize(iNativeOutputSampleRate, AudioFormat.CHANNEL_OUT_STEREO ,AudioFormat.ENCODING_PCM_16BIT);//sampleRateInHz, channelConfig, audioFormat) - this gave something much larger than native output buffer size.
        
		return iNativeOutputSampleRate;
	}
	
	private static int getNativeHardwareBufferSize() {
		int iNativeOutputBufferSize = 0;    

/*		if (android.os.Build.VERSION.SDK_INT >= 17) {
			Context context = Cocos2dxActivity.getContext();
			//@TargetApi(17)  // This should prevent lint from complaining (thogh it didn't anyway!
			if (context != null) {
				AudioManager audioManager = (AudioManager)context.getSystemService(Context.AUDIO_SERVICE);
				String siNativeOutputBufferSize = audioManager.getProperty(AudioManager.PROPERTY_OUTPUT_FRAMES_PER_BUFFER);
				iNativeOutputBufferSize = Integer.parseInt(siNativeOutputBufferSize);
				Log.d("Me","AudioManager gave native output buffer size: " + siNativeOutputBufferSize);
			}
		} 
*/
		return iNativeOutputBufferSize;
	}
	
	private static String getJavaRelaunchStringAndEmptyIt() {

/*		if (android.os.Build.VERSION.SDK_INT >= 17) {
			Context context = Cocos2dxActivity.getContext();
			//@TargetApi(17)  // This should prevent lint from complaining (thogh it didn't anyway!
			if (context != null) {
				AudioManager audioManager = (AudioManager)context.getSystemService(Context.AUDIO_SERVICE);
				String siNativeOutputBufferSize = audioManager.getProperty(AudioManager.PROPERTY_OUTPUT_FRAMES_PER_BUFFER);
				iNativeOutputBufferSize = Integer.parseInt(siNativeOutputBufferSize);
				Log.d("Me","AudioManager gave native output buffer size: " + siNativeOutputBufferSize);
			}
		} 
*/



	String sRet =  new String(LaunchFromWebActivity.sJavaRelaunchString);
	LaunchFromWebActivity.sJavaRelaunchString = new String(""); // Empty it!
		return sRet;
		
	}

	private static String getDeviceDescription() {
		// see - http://stackoverflow.com/questions/1995439/get-android-phone-model-programmatically
		//String manufacturer = android.os.Build.MANUFACTURER;
//		String brand = android.os.Build.BRAND;
//		String model = android.os.Build.MODEL;
		// Note that FINGERPRINT uniquely identifies build (and probably contains model no etc but not BRAND)
		/*if (model.startsWith(brand)) {
			//return capitalize(model);
			return model;
		} else {
			//return capitalize(manufacturer) + " " + model;
			return brand + " " + model;
		}*/
		return "android-" + android.os.Build.FINGERPRINT;
	}	


	private static String getAndroidId() {
		// for now just ANDROID_ID - though there are problems with this (it is randomly generated!!??) - eg see http://stackoverflow.com/questions/14891738/settings-secure-android-id-is-not-unique-how-to-solve
		// what is wrong with using mac address? http://stackoverflow.com/questions/17435538/using-android-mac-address-as-unique-identifier
		// how to actually get mac address - http://stackoverflow.com/questions/11705906/how-to-get-mac-address-device-in-android  note! need to handle situation that wifi is off!? unlikely if just downloaded but could be phone! so use phone num also as component!?)
		String android_id = Secure.getString(Cocos2dxActivity.getContext().getApplicationContext().getContentResolver(), Secure.ANDROID_ID);
		return android_id;
	}

	private static String getAndroidMacAddress() {
		WifiManager wifiMan = (WifiManager) Cocos2dxActivity.getContext().getSystemService(Cocos2dxActivity.WIFI_SERVICE);
		WifiInfo wifiInf = wifiMan.getConnectionInfo();
		return wifiInf.getMacAddress();
	}


	public static native void nativeRelaunch(final String sRelaunchString); // C++ code
	public static native boolean yDEBUG(); // C++ code

}
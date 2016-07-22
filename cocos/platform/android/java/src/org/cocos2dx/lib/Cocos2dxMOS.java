/* This file is my addition


TODO 
pdlib apparently does not use getNativeOutputSampleRate for pre openSl. So what does it use!?



LINKS
	http://stackoverflow.com/questions/11592820/writing-backwards-compatible-android-code
	pdlib - http://nettoyeur.noisepages.com/

*/


package org.cocos2dx.lib;

import android.content.Context;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.provider.Settings;
import android.provider.Settings.Secure;
import android.util.Log;

import com.mos.mindofsound.Cocos2dxMosActivity;
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
	/*
	private AudioManager.OnAudioFocusChangeListener mOnAudioFocusChangeListener;
	//…
	mOnAudioFocusChangeListener = new AudioManager.OnAudioFocusChangeListener() {
	 
				@Override
				public void onAudioFocusChange(int focusChange) {
					switch (focusChange) {
					case AudioManager.AUDIOFOCUS_GAIN:
						Log.i(TAG, "AUDIOFOCUS_GAIN");
	                                  // Set volume level to desired levels
						play();
						break;
					case AudioManager.AUDIOFOCUS_GAIN_TRANSIENT:
						Log.i(TAG, "AUDIOFOCUS_GAIN_TRANSIENT");
	                                  // You have audio focus for a short time
	                                  play();
						break;
					case AudioManager.AUDIOFOCUS_GAIN_TRANSIENT_MAY_DUCK:
						Log.i(TAG, "AUDIOFOCUS_GAIN_TRANSIENT_MAY_DUCK");
	                                  // Play over existing audio
	                                  play();
						break;
					case AudioManager.AUDIOFOCUS_LOSS:
						Log.e(TAG, "AUDIOFOCUS_LOSS");
						stop();
						break;
					case AudioManager.AUDIOFOCUS_LOSS_TRANSIENT:
						Log.e(TAG, "AUDIOFOCUS_LOSS_TRANSIENT");
	                                  // Temporary loss of audio focus - expect to get it back - you can keep your resources around
						pause();
						break;
					case AudioManager.AUDIOFOCUS_LOSS_TRANSIENT_CAN_DUCK:
						Log.e(TAG, "AUDIOFOCUS_LOSS_TRANSIENT_CAN_DUCK");
	                                  // Lower the volume
						break;
					}
				}
			};
			*/
		//static String sJavaRelaunchString = "Parameters!";
//private AudioManager.OnAudioFocusChangeListener afChangeListener;
	static AudioManager.OnAudioFocusChangeListener	afChangeListener = new AudioManager.OnAudioFocusChangeListener() {
		        public void onAudioFocusChange(int focusChange) {
		            if (focusChange == AudioManager.AUDIOFOCUS_LOSS_TRANSIENT) {
		            	Log.d("Me","AUDIOFOCUS_LOSS_TRANSIENT");
		            } else if (focusChange == AudioManager.AUDIOFOCUS_GAIN) {
		            	Log.d("Me","AUDIOFOCUS_LOSS_TRANSIENT");
		            } else if (focusChange == AudioManager.AUDIOFOCUS_LOSS) {
		                //am.unregisterMediaButtonEventReceiver(RemoteControlReceiver);
		                //am.abandonAudioFocus(afChangeListener);
		            	Log.d("Me","AUDIOFOCUS_LOSS");
		            } else {
		            	Log.d("Me","Unknown focusChange: " + focusChange);
		            	
		            }
		        }
		    };	
		    
/*	 IT'S ALREADY IN Device!		
private static void setKeepScreenOnFlag(boolean yVal) {
				// 2016_06_16 - http://discuss.cocos2d-x.org/t/prevent-screen-dimming/13837/2 - official docs: https://developer.android.com/training/scheduling/wakelock.html
				Log.d("Me","setKeepScreenOnFlag called !!!!!!!!!!!!!!");
				//Cocos2dxMosActivity.mActivity.requestWindowFeature(Window.FEATURE_NO_TITLE);
		        //getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
		        //    WindowManager.LayoutParams.FLAG_FULLSCREEN);
		        //setContentView(R.layout.main);
//				Cocos2dxMosActivity.mActivity.setContentView(Cocos2dxMosActivity.mActivity.mFrameLayout);
				if (yVal) {
					Cocos2dxMosActivity.mActivity.getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON); 
				} else {
					Cocos2dxMosActivity.mActivity.getWindow().clearFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
				}
				int fred = 0;
			}
*/			
			private static boolean getAudioFocus() {
				// Request audio focus for playback
				Context context = Cocos2dxActivity.getContext();
				AudioManager audioManager = (AudioManager)context.getSystemService(Context.AUDIO_SERVICE);
				int result = audioManager.requestAudioFocus(afChangeListener,
				                                 // Use the music stream.
				                                 AudioManager.STREAM_MUSIC,
				                                 // Request permanent focus.
				                                 AudioManager.AUDIOFOCUS_GAIN);
				
//				context.registerReceiver(new HeadsetPlugUnplugReceiver(), new IntentFilter(Intent.ACTION_HEADSET_PLUG));
				return (result == AudioManager.AUDIOFOCUS_REQUEST_GRANTED);
			}
	
//	HeadsetPlugUnplugReceiver fred = HeadsetPlugUnplugReceiver::getInstance();
	//HeadsetPlugUnplugReceiver fred = HeadsetPlugUnplugReceiver.getInstance();
	
	private static int getScreenOffTimeout() {
		// returns screen timeout in ms - returns zero if SCREEN_OFF_TIMEOUT is not defined
		return android.provider.Settings.System.getInt(Cocos2dxActivity.getContext().getContentResolver(), Settings.System.SCREEN_OFF_TIMEOUT, 0);//Integer.MAX_VALUE);
	}
	
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
	
	private static int getNativeHardwareBufferFrames() {
		/*
		 Note that property PROPERTY_OUTPUT_FRAMES_PER_BUFFER is defined to be native OR OPTIMAL value. Eg on my crap vodaphone it gives 1024 frames whereas my analysis software definitively deduced native hardware buffer to be 2048!
		 
		 */
		
		
		
		int iNativeOutputBufferFrames = 0;    

		if (android.os.Build.VERSION.SDK_INT >= 17) { // ie if build version of device is 4.2 or greater (ie second version of Jelly Bean)
			Context context = Cocos2dxActivity.getContext();
			//@TargetApi(17)  // This should prevent lint from complaining (though it didn't anyway!
			if (context != null) {
				AudioManager audioManager = (AudioManager)context.getSystemService(Context.AUDIO_SERVICE);
				String siNativeOutputBufferFrames = audioManager.getProperty(AudioManager.PROPERTY_OUTPUT_FRAMES_PER_BUFFER);
				iNativeOutputBufferFrames = Integer.parseInt(siNativeOutputBufferFrames);
				Log.d("Me","AudioManager gave siNativeOutputBufferFrames: " + siNativeOutputBufferFrames);
			}
		} 

		return 0;//iNativeOutputBufferFrames;// * 2; // debug - remove "*2"!!
	}

	private static boolean headsetStatusChanged() {
		// We want to record whether headser plugged=in status has changed since last call to this method.
		// We would like this to include usb headsets at some point!
		if (Cocos2dxMosActivity.yHeadsetPlugChanged) {
			Cocos2dxMosActivity.yHeadsetPlugChanged = false; // a bit crappy since might poss miss quickly following plug/unplug? actually maybe desirable to swallow fast subsequent...
			return true;
		} else {
			return false;
		}
	}
	
	private static String getJavaRelaunchStringAndEmptyIt() {

/*		if (android.os.Build.VERSION.SDK_INT >= 17) {
			Context context = Cocos2dxActivity.getContext();
			//@TargetApi(17)  // This should prevent lint from complaining (though it didn't anyway!
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
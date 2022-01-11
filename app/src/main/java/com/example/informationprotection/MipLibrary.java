package com.example.informationprotection;

import android.content.Context;

import java.lang.System;
import com.microsoft.applications.telemetry.core.InternalMgrImpl;
import com.microsoft.applications.telemetry.LogConfiguration;

public class MipLibrary {

    static {
        System.loadLibrary("mip_core");
        System.loadLibrary("mip_protection_sdk");
        System.loadLibrary("mip_upe_sdk");
        System.loadLibrary("miptest2");
    }

    synchronized static public int Init(Context context) {
        if (sMipLibrary == null)
            sMipLibrary = new MipLibrary();
        if (sLogConfiguration == null) {
            sLogConfiguration = InternalMgrImpl.getConfig();
        }
        return sMipLibrary.Init(context.getClass(), context);
    }

    native int Init(Class<?> contextClass, Context context);

    static private MipLibrary sMipLibrary;
    static private LogConfiguration sLogConfiguration;
}
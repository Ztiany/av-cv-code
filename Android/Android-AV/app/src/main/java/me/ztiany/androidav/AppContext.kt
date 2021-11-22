package me.ztiany.androidav

import android.app.Application
import android.content.Context
import kotlin.properties.Delegates
import timber.log.Timber


class AppContext : Application() {

    override fun onCreate() {
        super.onCreate()
        appContext = this
        Timber.plant(Timber.DebugTree())
    }

    companion object {

        private var appContext by Delegates.notNull<AppContext>()

        @JvmStatic
        fun get(): Context {
            return appContext
        }

    }

}
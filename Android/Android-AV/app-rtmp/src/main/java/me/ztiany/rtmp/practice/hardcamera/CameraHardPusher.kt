package me.ztiany.rtmp.practice.hardcamera

import me.ztiany.rtmp.common.Pusher
import me.ztiany.rtmp.practice.screen.VideoConfig
import me.ztiany.rtmp.practice.screen.ScreenVideoSource

class CameraHardPusher(
    private val videoConfig: VideoConfig,
    private val screenVideoSource: ScreenVideoSource
) : Pusher {

    override fun start(url:String) {

    }

    override fun stop() {

    }

    fun initSource() {

    }

    fun initPusher(url: String) {

    }

}
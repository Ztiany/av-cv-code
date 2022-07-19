package me.ztiany.androidav.audio.autiotrack

import android.net.Uri
import android.os.Bundle
import com.android.base.delegate.simpl.DelegateActivity
import com.android.sdk.mediaselector.common.ResultListener
import com.android.sdk.mediaselector.system.newSystemMediaSelector
import me.ztiany.androidav.databinding.AudioActivityMeAtBinding
import me.ztiany.androidav.player.mediacodec.printMediaTrackInfo
import timber.log.Timber

class MediaExtractorAudioTrackActivity : DelegateActivity() {

    private var selectedFile: Uri? = null

    private val systemMediaSelector by lazy {
        newSystemMediaSelector(this, object : ResultListener {
            override fun onTakeSuccess(result: List<Uri>) {
                Timber.d("onTakeSuccess: $result")
                selectedFile = result.getOrNull(0)
                showSelectedFile()
            }
        })
    }

    private fun showSelectedFile() {
        binding.audioSelectedFile.text = "已经选择：${selectedFile.toString()}"
    }

    private lateinit var binding: AudioActivityMeAtBinding

    private val mediaExtractorAudioTrackKit by lazy {
        MediaExtractorAudioTrackKit(this)
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = AudioActivityMeAtBinding.inflate(layoutInflater)
        setContentView(binding.root)
        setUpViews()
    }

    private fun setUpViews() {
        binding.audioSelectAudio.setOnClickListener {
            systemMediaSelector.takeFileFromSystem().mimeType("audio/*").start()
        }

        binding.audioSelectVideo.setOnClickListener {
            systemMediaSelector.takeFileFromSystem().mimeType("video/*").start()
        }

        binding.audioPrintTracks.setOnClickListener {
            selectedFile?.let {
                printMediaTrackInfo(this, it)
            }
        }

        binding.audioPlay.setOnClickListener {
            selectedFile?.let {
                mediaExtractorAudioTrackKit.play(it)
            }
        }

        binding.audioStop.setOnClickListener {
            mediaExtractorAudioTrackKit.stop()
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        mediaExtractorAudioTrackKit.stop()
    }

}
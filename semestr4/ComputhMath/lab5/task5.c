package com.example.android

import android.media.MediaPlayer
import android.os.Bundle
import android.os.Handler
import android.widget.Button
import android.widget.SeekBar
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.example.myapplication.R
import android.Manifest
import android.Manifest.permission.READ_EXTERNAL_STORAGE
import android.Manifest.permission.READ_MEDIA_AUDIO
import android.content.pm.PackageManager
import android.net.Uri
import android.os.Build
import android.os.Environment
import android.provider.MediaStore
import android.util.Log
import android.widget.Toast
import androidx.activity.result.contract.ActivityResultContracts
import java.io.File

class MP3 : AppCompatActivity() {
    private lateinit var prev: Button
    private lateinit var play: Button
    private lateinit var next: Button
    private lateinit var seekBar: SeekBar
    private lateinit var seekBarSound: SeekBar
    private lateinit var media: Array<MediaPlayer>
    private lateinit var cycle: Button
    private lateinit var runnable: Runnable
    private var track = 0
    private val handler = Handler()
    private var isCycleMode = false
    private var log_tag: String = "MY_LOG_TAG"

    private val requestPermissionLauncher = registerForActivityResult(
        ActivityResultContracts.RequestPermission()
    ) { isGranted ->
        if (isGranted) {
            playMusic()
        } else {
            Toast.makeText(this, "Permission denied - app cannot work without permissions", Toast.LENGTH_LONG).show()
            finish()
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_mp3)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        prev = findViewById(R.id.prevbtn)
        play = findViewById(R.id.playbtn)
        next = findViewById(R.id.nextbtn)
        seekBar = findViewById(R.id.seekbar)
        seekBarSound = findViewById(R.id.seekbarsound)
        cycle = findViewById(R.id.cyclebtn)

        if (checkSelfPermission(READ_MEDIA_AUDIO) == PackageManager.PERMISSION_GRANTED) {
            playMusic()
        } else {
            requestPermissionLauncher.launch(READ_MEDIA_AUDIO)
        }
    }

    private fun playMusic() {
        // Логирование пути и содержимого каталога Music
        val musicPath = Environment.getExternalStorageDirectory().path + "/Music"
        Log.d(log_tag, "PATH: $musicPath")

        val directory = File(musicPath)
        directory.listFiles()?.forEach {
            Log.d(log_tag, it.toString())
        }

        // Загрузка и воспроизведение музыки
        val musicDir = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_MUSIC)
        val files = musicDir.listFiles { file ->
            file.extension.equals("mp3", ignoreCase = true)
        }

        if (files != null && files.isNotEmpty()) {
            media = Array(files.size) { MediaPlayer() }
            for (i in files.indices) {
                media[i] = MediaPlayer().apply {
                    setDataSource(this@MP3, Uri.fromFile(files[i]))
                    prepare()
                }
            }

            // Инициализация слушателей
            media[track].setOnPreparedListener {
                seekBar.max = media[track].duration
                media[track].start() // Автоматически начинаем воспроизведение после подготовки
            }

            media.forEach { player ->
                player.setOnErrorListener { mp, what, extra ->
                    Log.e(log_tag, "MediaPlayer error: what=$what extra=$extra")
                    true
                }

                player.setOnCompletionListener {
                    if (isCycleMode) {
                        player.seekTo(0)
                        player.start()
                    } else {
                        player.stop()
                        player.prepare()
                        track = (track + 1) % media.size
                        media[track].start()
                        seekBar.max = media[track].duration
                    }
                }
            }
        } else {
            Toast.makeText(this, "No MP3 files found in Music directory", Toast.LENGTH_LONG).show()
            finish()
        }
    }
    override fun onResume() {
        super.onResume()
        play.setOnClickListener{
            if(!media[track].isPlaying){
                media[track].start()
            }else{
                media[track].pause()
            }
        }


        next.setOnClickListener{
            media[track].stop()
            media[track].prepare()

            track = (track + 1) % media.size
            media[track].start()
        }

        prev.setOnClickListener{
            media[track].stop()
            media[track].prepare()

            if(track <= 0){
                track = media.size - 1
            }else{
                track = (track - 1) % media.size
            }
        }

        cycle.setOnClickListener {
            isCycleMode = !isCycleMode
            cycle.isSelected = isCycleMode
            if (isCycleMode) {
                cycle.text = "Cycle ON"
            } else {
                cycle.text = "Cycle OFF"
            }
        }

        seekBar.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                if (fromUser) {
                    media[track].seekTo(progress)
                }
            }

            override fun onStartTrackingTouch(seekBar: SeekBar?) {

            }
            override fun onStopTrackingTouch(seekBar: SeekBar?) {

            }
        })

        runnable = Runnable {
            seekBar.progress = media[track].currentPosition
            handler.postDelayed(runnable, 0)
            media[track].setOnCompletionListener {
                if (isCycleMode) {
                    media[track].seekTo(0)
                    media[track].start()
                } else {
                    media[track].stop()
                    media[track].prepare()
                    track = (track + 1) % media.size
                    media[track].start()
                    seekBar.max = media[track].duration
                }
            }


        }
        handler.postDelayed(runnable, 0)


        seekBarSound.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                if (fromUser) {
                    val volume = progress / 100f
                    media[track].setVolume(volume, volume)


                }
            }

            override fun onStartTrackingTouch(seekBar: SeekBar?) {}
            override fun onStopTrackingTouch(seekBar: SeekBar?) {}
        })


        seekBarSound.progress = 100
        media[track].setVolume(1f, 1f)

    }

    override fun onDestroy() {
        super.onDestroy()
        handler.removeCallbacks(runnable)

        media.forEach { player ->
            player.release()
        }
    }
}
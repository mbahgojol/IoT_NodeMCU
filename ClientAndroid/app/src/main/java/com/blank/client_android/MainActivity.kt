package com.blank.client_android

import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import io.socket.client.IO
import io.socket.client.Socket
import kotlinx.android.synthetic.main.activity_main.*

const val TAG = "MainActivity"

class MainActivity : AppCompatActivity() {

    private val socket: Socket by lazy {
        IO.socket("http://192.168.43.33:3000")
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        socket.connect()

        socket.on("connect") {
            socket.emit("join", "Android Connected")
        }

        socket.on("disconnect") {
            Log.d(TAG, "Socket Disconnect")
        }

        nyala.setOnClickListener {
            socket.emit("send", "1")
        }

        mati.setOnClickListener {
            socket.emit("send", "0")
        }
    }
}

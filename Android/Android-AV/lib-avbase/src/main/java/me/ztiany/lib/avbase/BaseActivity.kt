package me.ztiany.lib.avbase

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.viewbinding.ViewBinding

open class BaseActivity<VB : ViewBinding> : AppCompatActivity() {

    private lateinit var _binding: VB

    protected val binding: VB
        get() = _binding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        beforeSetUpView()
        _binding = inflateBindingWithParameterizedType(layoutInflater)
        setContentView(_binding.root)
        setUpView()
    }

    protected open fun beforeSetUpView() {

    }

    protected open fun setUpView() {

    }

}
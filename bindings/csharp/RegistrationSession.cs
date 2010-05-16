/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class RegistrationSession : SipSession {
  private HandleRef swigCPtr;

  internal RegistrationSession(IntPtr cPtr, bool cMemoryOwn) : base(tinyWRAPPINVOKE.RegistrationSessionUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(RegistrationSession obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~RegistrationSession() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          tinyWRAPPINVOKE.delete_RegistrationSession(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public RegistrationSession(SipStack Stack) : this(tinyWRAPPINVOKE.new_RegistrationSession(SipStack.getCPtr(Stack)), true) {
  }

  public bool Register() {
    bool ret = tinyWRAPPINVOKE.RegistrationSession_Register(swigCPtr);
    return ret;
  }

  public bool UnRegister() {
    bool ret = tinyWRAPPINVOKE.RegistrationSession_UnRegister(swigCPtr);
    return ret;
  }

}

;; Auto-generated. Do not edit!


(when (boundp 'KeyPad::where)
  (if (not (find-package "KEYPAD"))
    (make-package "KEYPAD"))
  (shadow 'where (find-package "KEYPAD")))
(unless (find-package "KEYPAD::WHERE")
  (make-package "KEYPAD::WHERE"))

(in-package "ROS")
;;//! \htmlinclude where.msg.html


(defclass KeyPad::where
  :super ros::object
  :slots (_data ))

(defmethod KeyPad::where
  (:init
   (&key
    ((:data __data) 0)
    )
   (send-super :init)
   (setq _data (round __data))
   self)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:serialization-length
   ()
   (+
    ;; int32 _data
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _data
       (write-long _data s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _data
     (setq _data (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get KeyPad::where :md5sum-) "da5909fbe378aeaf85e547e830cc1bb7")
(setf (get KeyPad::where :datatype-) "KeyPad/where")
(setf (get KeyPad::where :definition-)
      "int32 data

")



(provide :KeyPad/where "da5909fbe378aeaf85e547e830cc1bb7")



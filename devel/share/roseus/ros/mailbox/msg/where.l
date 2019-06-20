;; Auto-generated. Do not edit!


(when (boundp 'mailbox::where)
  (if (not (find-package "MAILBOX"))
    (make-package "MAILBOX"))
  (shadow 'where (find-package "MAILBOX")))
(unless (find-package "MAILBOX::WHERE")
  (make-package "MAILBOX::WHERE"))

(in-package "ROS")
;;//! \htmlinclude where.msg.html


(defclass mailbox::where
  :super ros::object
  :slots (_data ))

(defmethod mailbox::where
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

(setf (get mailbox::where :md5sum-) "da5909fbe378aeaf85e547e830cc1bb7")
(setf (get mailbox::where :datatype-) "mailbox/where")
(setf (get mailbox::where :definition-)
      "int32 data

")



(provide :mailbox/where "da5909fbe378aeaf85e547e830cc1bb7")



; Auto-generated. Do not edit!


(cl:in-package KeyPad-msg)


;//! \htmlinclude where.msg.html

(cl:defclass <where> (roslisp-msg-protocol:ros-message)
  ((data
    :reader data
    :initarg :data
    :type cl:integer
    :initform 0))
)

(cl:defclass where (<where>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <where>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'where)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name KeyPad-msg:<where> is deprecated: use KeyPad-msg:where instead.")))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <where>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader KeyPad-msg:data-val is deprecated.  Use KeyPad-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <where>) ostream)
  "Serializes a message object of type '<where>"
  (cl:let* ((signed (cl:slot-value msg 'data)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <where>) istream)
  "Deserializes a message object of type '<where>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'data) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<where>)))
  "Returns string type for a message object of type '<where>"
  "KeyPad/where")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'where)))
  "Returns string type for a message object of type 'where"
  "KeyPad/where")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<where>)))
  "Returns md5sum for a message object of type '<where>"
  "da5909fbe378aeaf85e547e830cc1bb7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'where)))
  "Returns md5sum for a message object of type 'where"
  "da5909fbe378aeaf85e547e830cc1bb7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<where>)))
  "Returns full string definition for message of type '<where>"
  (cl:format cl:nil "int32 data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'where)))
  "Returns full string definition for message of type 'where"
  (cl:format cl:nil "int32 data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <where>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <where>))
  "Converts a ROS message object to a list"
  (cl:list 'where
    (cl:cons ':data (data msg))
))

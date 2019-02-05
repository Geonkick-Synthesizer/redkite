class RkEvent {
 public:        
      enum Type {
	   None,
	   Close,
	   Hide,
	   Show,
	   KeyPress,
	   KeyRelease,
	   MouseMove,
	   MouseButtonPress,
	   MouseButtonRelease,
	   Wheel,
	   Move,
	   Pain,
	   Expose
      };

      RkEvent()
      virtual ~Rkevent();
      Type type();

    private:
      RK_PRIVATE_IMPL(RkEvent, privateEvent)
};

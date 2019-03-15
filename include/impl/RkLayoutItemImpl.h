
class RkLayoutItem {
 public:
        enum class Type : int {
                Widget,
                Space,
                Layout
        };

        enum  Alignment : int {
                AlignLeft,
                AlignRight,
        };

        RkLayoutItem();
        virtual ~RkLayoutItem();
        Type type() const;
        Alignemnt alignment() const;
        void setAlignemnt(Alignment align);
        virtual std::pair<int, int> minimumSize() const = 0;
        virtual std::pair<int, int> maximumSize() const = 0;
        virtual setSize(const std::pair<int, int> &size) = 0;

 private:
        Type itemType;
        Alignment itemAlignemnt;
};

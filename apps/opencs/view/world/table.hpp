#ifndef CSV_WORLD_TABLE_H
#define CSV_WORLD_TABLE_H

#include <vector>
#include <string>

#include <QTableView>

class QUndoStack;
class QAction;

namespace CSMWorld
{
    class Data;
    class UniversalId;
    class IdTableProxyModel;
    class IdTable;
}

namespace CSVWorld
{
    class CommandDelegate;

    ///< Table widget
    class Table : public QTableView
    {
            Q_OBJECT

            std::vector<CommandDelegate *> mDelegates;
            QUndoStack& mUndoStack;
            QAction *mEditAction;
            QAction *mCreateAction;
            QAction *mRevertAction;
            QAction *mDeleteAction;
            CSMWorld::IdTableProxyModel *mProxyModel;
            CSMWorld::IdTable *mModel;
            bool mEditLock;
            int mRecordStatusDisplay;

        private:

            void contextMenuEvent (QContextMenuEvent *event);

            std::vector<std::string> listRevertableSelectedIds() const;

            std::vector<std::string> listDeletableSelectedIds() const;

        public:

            Table (const CSMWorld::UniversalId& id, CSMWorld::Data& data, QUndoStack& undoStack, bool createAndDelete);
            ///< \param createAndDelete Allow creation and deletion of records.

            void setEditLock (bool locked);

            CSMWorld::UniversalId getUniversalId (int row) const;

            void updateEditorSetting (const QString &settingName, const QString &settingValue);

        signals:

            void editRequest (int row);

            void selectionSizeChanged (int size);

            void tableSizeChanged (int size, int deleted, int modified);
            ///< \param size Number of not deleted records
            /// \param deleted Number of deleted records
            /// \param modified Number of added and modified records

            void createRequest();

        private slots:

            void revertRecord();

            void deleteRecord();

            void editRecord();

        public slots:

            void tableSizeUpdate();

            void selectionSizeUpdate();

            void requestFocus (const std::string& id);

    };
}

#endif

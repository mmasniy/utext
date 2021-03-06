#include "emptywidget.h"
#include "texteditor.h"
#include "tabchanger.h"

EmptyWidget::EmptyWidget(QWidget *parent) : QWidget(parent) {
    auto gridLayout = new QGridLayout;
    gridLayout->setMargin(0);
    setLayout(gridLayout);
    setLayoutDirection(Qt::LayoutDirection::LeftToRight);
    m_split = new QSplitter(Qt::Orientation::Vertical, this);
    layout()->addWidget(m_split);
    setAcceptDrops(true);
}

void EmptyWidget::dropEvent(QDropEvent *event) {
    if (!event->mimeData()->hasUrls())
        return;
    auto files = event->mimeData()->urls();

    for (const auto &file : files) {
        AddPageToLastFocus(file.fileName(), new QFile(file.fileName()));
    }
}
void EmptyWidget::dragEnterEvent(QDragEnterEvent *event) {
    event->acceptProposedAction();
}
void EmptyWidget::dragMoveEvent(QDragMoveEvent *event) {
    event->accept();
}
void EmptyWidget::dragLeaveEvent(QDragLeaveEvent *event) {
    event->accept();
}
void EmptyWidget::addNewWindow(TabChanger *tabs) {
    connect(tabs, &TabChanger::SplitHorizontaly, this, &EmptyWidget::Split);
    connect(tabs, &TabChanger::SplitVerticaly, this, &EmptyWidget::Split);
    while (tabs->y() >= m_split->count()) {
        m_split->addWidget(new QSplitter(Qt::Orientation::Horizontal, this));
    }
    if (tabs->y() == -1) {
        m_split->insertWidget(0, new QSplitter(Qt::Orientation::Horizontal, this));
        dynamic_cast<QSplitter *>(m_split->widget(0))->insertWidget(tabs->x(), tabs);
    } else {
        dynamic_cast<QSplitter *>(m_split->widget(tabs->y()))->addWidget(tabs);
    }
}

void EmptyWidget::Split(const int x, const int y, QWidget *editor) {
    TabChanger *tab = new TabChanger(x, y, this);

    connect(tab, &TabChanger::TabFocused, this, &EmptyWidget::LastFocusedTabController);
    addNewWindow(tab);
    tab->AddPage(editor);
}

void EmptyWidget::LastFocusedTabController(QWidget *widget) {
    m_lastFocus = widget;
}

void EmptyWidget::AddPageToLastFocus(QString label, QFile *file) {
    if (m_lastFocus)
        dynamic_cast<TabChanger *>(m_lastFocus)->AddPage(label, file);
    else if (m_split->findChild<TabChanger *>())
        m_split->findChild<TabChanger *>()->AddPage(label, file);
    else {
        TabChanger *tab = new TabChanger(0, 0, this);
        connect(tab, &TabChanger::TabFocused, this, &EmptyWidget::LastFocusedTabController);
        addNewWindow(tab);
        tab->AddPage(label, file);
    }
}

EmptyWidget::~EmptyWidget() {
    delete m_split;
}

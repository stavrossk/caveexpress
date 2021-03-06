#include "UINodePaymentSelector.h"
#include "engine/client/ui/UI.h"
#include "engine/common/System.h"
#include "engine/common/Payment.h"
#include "engine/common/Logger.h"

UINodePaymentSelector::UINodePaymentSelector(IFrontend *frontend, int rows) :
		UINodeBackgroundSelector<PaymentEntry>(frontend, 1, rows)
{
	_colWidth = _size.x;
	setScrollingEnabled(true);
	setPageVisible(true);
	setBorder(true);
	setRowSpacing(10);
	setFont(HUGE_FONT);
	setRowHeight(getFontHeight() / static_cast<float>(_frontend->getHeight()) * 2.0f);
	setAutoColsRows();
	autoSize();
}

UINodePaymentSelector::~UINodePaymentSelector()
{
}

std::string UINodePaymentSelector::getText (const PaymentEntry& data) const
{
	return data.name + " (" + data.price + ")";
}

void UINodePaymentSelector::renderSelectorEntry (int index, const PaymentEntry& data, int x, int y, int colWidth, int rowHeight, float alpha) const
{
	Color color = { 0.6f, 0.6f, 0.6f, 0.6f };
	if (_selectedIndex == index) {
		color[0] = color[1] = color[2] = 1.0f;
		color[3] = 0.3f;
	} else if ((index % 2) == 0) {
		color[3] = 0.3f;
	}
	_frontend->renderFilledRect(x, y, colWidth, rowHeight, color);
	UINodeBackgroundSelector<PaymentEntry>::renderSelectorEntry(index, data, x, y, colWidth, rowHeight, alpha);
}

bool UINodePaymentSelector::onPush ()
{
	reset();
	return true;
}

void UINodePaymentSelector::reset ()
{
	UINodeBackgroundSelector<PaymentEntry>::reset();
	std::vector<PaymentEntry> e;
	System.getPaymentEntries(e);
	for (std::vector<PaymentEntry>::const_iterator i = e.begin(); i != e.end(); ++i) {
		if (!System.hasItem(i->id))
			addData(*i);
	}
}

bool UINodePaymentSelector::onSelect (const PaymentEntry& data)
{
	if (!System.buyItem(data.id)) {
		error(LOG_CLIENT, "failed to buy item " + data.id);
		return true;
	}

	UI::get().initRestart();
	info(LOG_CLIENT, "bought item " + data.id);
	return true;
}

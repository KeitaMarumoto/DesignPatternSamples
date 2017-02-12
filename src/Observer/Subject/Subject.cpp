#include "Subject.h"

//オブザーバの登録
//observer_node_ 登録したいオブザーバをもつノード
//observer_ 登録したいオブザーバ本体
void Subject::addObserver(ObserverNode* observer_node_, Observer* observer_)
{
	//今現在あるオブザーバの先頭に新たなオブザーバを挿入。
	observer_node_->next_ = head_;
	observer_node_->observer_ = observer_;
	head_ = observer_node_;
}

//登録してあるオブザーバの解除
//observer_node_ 登録解除したいオブザーバのノード
void Subject::removeObserver(ObserverNode* observer_node_)
{
	//削除対象が先頭の場合のみ例外的。
	if (head_ == observer_node_) {
		head_ = observer_node_->next_;
		observer_node_->next_ = nullptr;
		observer_node_->observer_ = nullptr;
		return;
	}

	//2番目以降はオブザーバのリストの最後まで回り
	//削除対象の次のポインタを削除対象の前のnext_につなぎなおしてからnullptrを代入。
	ObserverNode* current_node_ = head_;
	while (current_node_ != nullptr) {
		if (current_node_->next_ == observer_node_) {
			current_node_->next_ = observer_node_->next_;
			observer_node_->next_ = nullptr;
			observer_node_->observer_ = nullptr;
			return;
		}

		current_node_ = current_node_->next_;
	}
}

//各オブザーバへの通知を送信
void Subject::notify(Entity & entity_, Events event_)
{
	ObserverNode* observer_node_ = head_;

	while (observer_node_ != nullptr) 
	{
		observer_node_->observer_->onNotify(entity_, event_);
		observer_node_ = observer_node_->next_;
	}
}

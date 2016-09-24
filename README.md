# ProjectionMapping
## 入力値
### 心拍データ
- beat_detect[0]:Arduinoからの人間の心拍
- beat_detect[1~6]:間欠カオス法で生成した人工心拍
鼓動のタイミングで1を受信、その他は0を受信し続ける。  
### FFT解析データ
- lowValue:低周波数帯
- midValue:中周波数帯
- highValue:高周波数帯
Float値で受信。送信側のGUI操作でLevelをMAP関数で変更可能。

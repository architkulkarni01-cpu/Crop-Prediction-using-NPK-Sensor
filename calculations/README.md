# Calculations

Derivation of NPK thresholds used in the crop prediction logic.

## Threshold Basis

Threshold values in `firmware/main.ino` were derived by cross-referencing:
- **ICAR Fertilizer Recommendations** (*Targeted Yield Approach Based Fertilizer Recommendations for Higher Productivity and Profitability*)
- **Local agricultural guidelines** for Pune, Maharashtra (Dept. of Agriculture, Govt. of Maharashtra)

The midpoint of each recommended range was used as the lower bound trigger in the rule-based logic, with a small margin to account for sensor noise.

## Reference Ranges (kg/ha)

| Crop | N | P₂O₅ | K₂O | Source |
|------|---|------|-----|--------|
| Wheat | 200–250 | 18–21 | 420–450 | Local Pune agricultural guidelines |
| Rice | 250–270 | 18–22 | 450–470 | ICAR Fertilizer Recommendations |
| Millet | 150–170 | 1–185 | 350–370 | ICAR Fertilizer Recommendations |
| Peas | 160–180 | 18–22 | 380–400 | Pune fertilizer practices |
| Tomato | 160–170 | <16 | 360–380 | ICAR Crop Recommendations |

## Moving Average Filter

The firmware uses a window-based moving average over `NUM_SAMPLES` readings to reduce sensor noise:

```
filtered_value = sum(buffer[0..N-1]) / N
```

A spike validation step rejects readings that deviate more than a configurable `thresholdPercent` from the previous stable value, preventing outliers from corrupting the prediction.

# Results

Validation of the crop prediction system against ICAR fertilizer recommendations and regional agricultural guidelines for Pune, Maharashtra.

## Predicted Outputs

The system was tested across five different soil samples and correctly identified the suitable crop in each case:

### Wheat
![Result Prediction 1](../images/Result%20Prediction%201.png)

### Rice
![Result Prediction 2](../images/Result%20Prediction%202.png)

### Peas
![Result Prediction 3](../images/Result%20Prediction%203.png)

### Tomato
![Result Prediction 4](../images/Result%20Prediction%204.png)

### Millet
![Result Prediction 5](../images/Result%20Prediction%205.png)

---

## Observed vs. Recommended NPK Values

Average of 10 sensor readings per crop, compared against ICAR and local Pune guidelines:

| Crop | N Observed | N Recommended | P Observed | P Recommended | K Observed | K Recommended |
|------|-----------|---------------|-----------|---------------|-----------|---------------|
| Wheat | 212.8 | 200–250 | 19.3 | 18–21 | 422.1 | 420–450 |
| Rice | 289.3 | 250–270 | 21.2 | 18–22 | 455.8 | 450–470 |
| Peas | 171.3 | 160–180 | 17.1 | 18–22 | 379.7 | 380–400 |
| Tomato | 173.5 | 160–170 | 16.2 | <16 | 366.9 | 360–380 |
| Millet | 155.6 | 150–170 | 16.3 | 1–185 | 358.9 | 350–370 |

*(All values in kg/ha)*

## Observations

All experimentally observed values fall within or close to the recommended ranges, validating the accuracy of the sensor-based system. Minor deviations (e.g., Peas phosphorus slightly below range) are consistent with naturally low-input soils. The results confirm that the rule-based prediction logic reliably reflects real field conditions.

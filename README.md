# ESPHome mcp4xxx

The mcp4xxx component enables the use of 7-bit digital potentiometers/rheostats via SPI. This includes the [MCP413x](https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/DataSheets/22060b.pdf) and [MCP414x](https://ww1.microchip.com/downloads/en/DeviceDoc/22059b.pdf) series.

## Examples

### Basic digipot

```yaml
external_components:
  - source:
      type: git
      url: https://git.ellis.codes/e/esphome-mcp4xxx.git
      ref: main
    components: [mcp4xxx]

spi:
  clk_pin: GPIO19
  mosi_pin: GPIO20

mcp4xxx:
  - cs_pin: GPIO18
    name: "Digital Potentiometer"
```

### Digipot as a fan

```yaml
external_components:
  - source:
      type: git
      url: https://git.ellis.codes/e/esphome-mcp4xxx.git
      ref: main
    components: [mcp4xxx]

spi:
  clk_pin: GPIO19
  mosi_pin: GPIO20

mcp4xxx:
  - id: digipot
    internal: true
    cs_pin: GPIO18

fan:
  - platform: mcp4xxx
    mcp4xxx_id: digipot
    name: "Digipot Fan"
```

## Configuration variables

### `mcp4xxx` component

- **id** (_Optional_, ID): The id to use for this output component.
- **initial_value** (_Optional_, int): Manually specify the initial value for the wiper pin. Defaults to `0`.

### Fan component

- **id** (_Optional_, ID): The id to use for this output component.
- **mcp4xxx_id** (_Required_, ID): The id of the mcp4xxx component to control.
- **speed_count** (_Optional_, int, max. `128`): The number of distinct speed levels. Defaults to `100`. Speed levels are automatically spread evenly across the 7-bit range.

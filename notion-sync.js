const { Client } = require('@notionhq/client');
const fs = require('fs');
const path = require('path');

// 你的配置
const NOTION_TOKEN = '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';
const NOTION_PAGE_ID = '1ecf149f-bcdc-80c2-a65e-ea8c95ffa02e';
const HEXO_POSTS_DIR = path.join(__dirname, 'source/_posts/notion');

// 初始化客户端
const notion = new Client({
  auth: NOTION_TOKEN,
  headers: {
    'Content-Type': 'application/json; charset=utf-8',
    'Accept': 'application/json; charset=utf-8'
  }
});

// 创建目录
if (!fs.existsSync(HEXO_POSTS_DIR)) {
  fs.mkdirSync(HEXO_POSTS_DIR, { recursive: true, encoding: 'utf8' });
}

// 工具函数：提取块的文本内容（兼容所有情况）
function extractBlockText(block) {
  // 处理空rich_text
  if (!block[block.type]?.rich_text || block[block.type].rich_text.length === 0) {
    return '';
  }
  // 拼接所有rich_text片段（解决只取[0]的问题）
  return block[block.type].rich_text.map(t => {
    // 兼容plain_text/Text对象
    return t.plain_text || t.text?.content || '';
  }).join('').trim();
}

// 核心同步逻辑
async function syncPageWithAllContent() {
  try {
    // 1. 获取页面标题
    const page = await notion.pages.retrieve({ page_id: NOTION_PAGE_ID });
    const title = page.properties?.title?.title[0]?.plain_text || '帅哥的博客';

    // 2. 获取所有块（分页拉取，避免漏块）
    let allBlocks = [];
    let startCursor = null;
    do {
      const blocks = await notion.blocks.children.list({
        block_id: NOTION_PAGE_ID,
        page_size: 100,
        start_cursor: startCursor
      });
      allBlocks = [...allBlocks, ...blocks.results];
      startCursor = blocks.next_cursor;
    } while (startCursor);

    // 3. 拼接MD内容（兼容所有文本块）
    let mdContent = `---
title: ${title}
date: ${new Date().toISOString().slice(0, 19).replace('T', ' ')}
categories: Notion笔记
tags: [Notion]
---

# ${title}
`;

    // 遍历所有块，转换为MD
    allBlocks.forEach(block => {
      const text = extractBlockText(block);
      if (!text) return; // 跳过空文本块

      switch (block.type) {
        case 'paragraph':
          mdContent += `${text}\n\n`;
          break;
        case 'heading_1':
          mdContent += `# ${text}\n\n`;
          break;
        case 'heading_2':
          mdContent += `## ${text}\n\n`;
          break;
        case 'heading_3':
          mdContent += `### ${text}\n\n`;
          break;
        case 'bulleted_list_item':
          mdContent += `- ${text}\n\n`;
          break;
        case 'numbered_list_item':
          mdContent += `1. ${text}\n\n`;
          break;
        case 'code':
          const lang = block.code.language || 'plaintext';
          mdContent += `\`\`\`${lang}\n${text}\n\`\`\`\n\n`;
          break;
        case 'quote':
          mdContent += `> ${text}\n\n`;
          break;
        // 可继续扩展：table、callout等
        default:
          // 非文本块也保留提示，避免内容丢失
          mdContent += `<!-- 未支持的块类型：${block.type} -->\n\n`;
          break;
      }
    });

    // 兜底：若内容为空，添加默认文本
    if (mdContent.length < 200) { // 仅Front-matter，无正文
      mdContent += '\n\n> 【Notion同步】该页面暂无文本内容，若有内容但未显示，请检查块类型是否支持。\n\n';
    }

    // 4. 写入文件
    const safeTitle = title.replace(/[\\/:*?"<>|]/g, '-');
    const mdPath = path.join(HEXO_POSTS_DIR, `${safeTitle}.md`);
    fs.writeFileSync(mdPath, mdContent, { encoding: 'utf8' });
    console.log(`✅ 同步成功！MD文件路径：${mdPath}`);
    console.log(`✅ MD文件内容预览：\n${mdContent.substring(0, 500)}...`);

  } catch (err) {
    console.error('❌ 同步失败：', err.message);
    if (err.stack) console.error('错误堆栈：', err.stack.slice(0, 300));
  }
}

// 执行同步
syncPageWithAllContent();